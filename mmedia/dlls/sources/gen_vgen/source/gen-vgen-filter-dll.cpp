/**
\file       gen-vgen-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_gen_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "gen-vgen-includes_int.hpp"
#include "gen-vgen-info-filter-dll.hpp"
#include "gen-vgen-filter-dll.hpp"

#include <algorithm>
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::sources::gen_vgen
{
::libs::utility::dlls::FreezerDlls Filter::frozen_dlls_;

Filter::Filter ()
{
  events2funcs_[syn::BufsEvent::gen_get_mid ()] =
    [this] (syn::CallInterfInfo& info) -> void {
    auto* devent = ::libs::iproperties::helpers::cast_event< syn::BufsEvent > (info.event_);
    fill_buf (&finfo_, devent);
  };

  events2funcs_[syn::ChangeStateProcessEvent::gen_get_mid ()] =
    [this] (syn::CallInterfInfo& info) -> void {
    auto* event = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (info.event_);
    if (event->is_start ())
    {
      update_source_driver (&finfo_);
    }
    else
    {
      if (auto source_impl = finfo_.proxy2hardware_.get_source_impl ())
      {
        source_impl->stop ();
      }
    }
  };

  events2funcs_[syn::ListDevicesDataEvent::gen_get_mid ()] =
    [this] (syn::CallInterfInfo& info) -> void {
    auto*                                     event = ::libs::iproperties::helpers::cast_event< syn::ListDevicesDataEvent > (info.event_);
    syn::ListDevicesDataEvent::src_names_type types;

    idata_source_impl_.get_types (types);
    U3_LOG_DATA_DBG ("before clear" + VTOLOG (types.size ()));
    // Чистим от расширений, чтобы передавать далее кроссплатформенный вид
    for (auto& type : types)
    {
      type = type.substr (0, type.find (::libs::utility::dlls::get_dll_suffix ()));
    }

    U3_LOG_DATA_DBG ("after clear" + VTOLOG (types.size ()));
    event->set_source_dll_names (std::move (types));

    auto source_dll_names = event->get_source_dll_names ();

    std::size_t indx = 0;
    for (const auto& source_dll_name : source_dll_names)
    {
      U3_LOG_DATA_DBG (VTOLOG (indx) + TOLOG (source_dll_name));
      syn::ListDevicesDataEvent::src_infos_type sources;

      idata_source_impl_.get_sources (source_dll_name, sources);
      event->set_devices_for_dll (indx, std::move (sources));
      ++indx;
    }
  };
}


void
Filter::thread_func_impl (std::uint32_t indx_thread)
{
#ifdef U3_OS_WIN32_DESKTOP
  U3_CHECK (SUCCEEDED (CoInitializeEx (0, COINIT_MULTITHREADED)), "CoInitializeEx");   //  данная подсистема (COM) нужна, пока я использую DirectShow источники данных в адресном пространстве процесса под Win32
#endif

  bool frame_loaded = true;
  auto now_delay    = consts::ms_delay_skip_cycle;

  do
  {
    if (!frame_loaded && now_delay.count ())
    {
      //  Если буфер не был сформирован - вставляем задержку, чтобы не загружать систему.
      U3_LOG_DATA_TIMING ("gen vgen thread sleep" + VTOLOG (now_delay.count ()));
      std::this_thread::sleep_for (std::chrono::milliseconds (now_delay));
      now_delay = consts::ms_delay_skip_cycle;
    }

    frame_loaded = false;

    const auto srcimpl = finfo_.proxy2hardware_.get_source_impl ();

    {
      std::unique_lock< InfoFilter::sync_type > lock (finfo_.wdmtx_, consts::ms_wait_capture_device);
      if (!lock.owns_lock ())
      {
        U3_LOG_DATA_ERROR ("failed acquired mutex" + VTOLOG (consts::ms_wait_capture_device.count ()) + "ms");
        continue;
      }

      //  получен сигнал на выход - завершаем работу
      if (finfo_.stop_req_)
      {
        return;
      }

      {
        const auto srcstared = srcimpl ? srcimpl->is_source_started () : false;
        if (!srcstared)
        {
          // Графы обработки данных могут использоваться получения информации об окружении (например для получения списка устройства из dll),
          // а не только для получения данных. Поэтому данная ситуация допустима.
          U3_LOG_DATA_DATA ("empty source impl or not started" + TOLOG (finfo_.rprops_->name_impl_dll_) + TOLOG (finfo_.rprops_->device_name_) + VTOLOG (finfo_.rprops_->device_indx_) + VTOLOG (srcstared));
          now_delay = consts::ms_delay_skip_cycle_before_start_device;
          continue;
        }
      }
      // Пока еще драйвер не загружен
      if (!finfo_.links_props_.pdriver2buf_)
      {
        U3_LOG_DATA_DEV ("empty driver driver2buf_" + TOLOG (finfo_.rprops_->name_impl_dll_));
        now_delay = consts::ms_delay_skip_cycle_before_start_device;
        continue;
      }
      // Количество уже захваченных кадров больше или равно максимальному - переходим на засыпание
      if (finfo_.impl_frames_.size () >= finfo_.capture_props_->capi_.count_preload_frame_)
      {
        continue;
      }
      //  контроль частоты обработки кадров с данного устройства.
      if (!finfo_.capture_fps_.is_action ())
      {
        continue;
      }
    }

    auto pdriver2buf_impl = finfo_.links_props_.pdriver2buf_->impl ();
    auto new_bufs         = std::make_shared< ::dlls::sources::gen_lib::syn::keys2bufs_type > ();
    auto gnew_buf         = pdriver2buf_impl->create (0);
    auto gnew_codec_buf   = pdriver2buf_impl->create (0);

    (*new_bufs)[::utils::dbufs::video::consts::offs::raw]  = gnew_buf;
    (*new_bufs)[::utils::dbufs::video::consts::offs::mjpg] = gnew_codec_buf;

    gnew_buf->flush ();
    gnew_codec_buf->flush ();

    {
      syn::tevents_type impl_events;
      srcimpl->get_raw_data (new_bufs, &impl_events);
      for (auto& new_buf : (*new_bufs))
      {
        //  достаточно любого непустого буфера внутри метабуфера, чтобы произвести передачу всей структуры дальше.
        if (new_buf.second && !new_buf.second->get_flag (utils::dbufs::BufFlags::empty))
        {
          frame_loaded = true;
          break;
        }
      }

      {
        std::unique_lock< InfoFilter::sync_type > lock (finfo_.wdmtx_, consts::ms_wait_capture_device);
        if (!lock.owns_lock ())
        {
          U3_LOG_DATA_ERROR ("failed acquired mutex" + VTOLOG (consts::ms_wait_capture_device.count ()) + "ms");
          continue;
        }
        if (frame_loaded)
        {
          finfo_.impl_frames_.push_back (new_bufs);
        }

        std::ranges::copy (impl_events, std::back_inserter (events_from_impl_));
        impl_events.clear ();
      }
    }
  } while (true);
}


void
Filter::thread_postfunc_impl (std::uint32_t indx_thread)
{
}
}   // namespace dlls::sources::gen_vgen
