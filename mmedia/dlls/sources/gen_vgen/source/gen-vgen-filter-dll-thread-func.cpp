/**
\file       gen-vgen-filter-dll-thread-funct.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.04.2016
\project    u3_gen_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "gen-vgen-includes_int.hpp"
#include "gen-vgen-info-filter-dll.hpp"
#include "gen-vgen-filter-dll.hpp"

namespace dlls::sources::gen_vgen
{
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

        std::copy (impl_events.begin (), impl_events.end (), std::back_inserter (events_from_impl_));
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
