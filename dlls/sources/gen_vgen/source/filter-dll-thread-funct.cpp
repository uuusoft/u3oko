//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-thread_funct.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       23.04.2016
\copyright  www.uuusoft.com
\project    uuu_gen_vgen
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace sources { namespace gen_vgen {

void
Filter::thread_funct_impl (std::size_t _indx_thread)
{
#if defined(UUU_OS_WIN32_DESKTOP)
  //  данная подсистема нужна, пока я использую DirectShow источники данных в адресном пространстве процесса
  CHECK_CALL (SUCCEEDED (CoInitializeEx (0, COINIT_MULTITHREADED)), "failed CoInitializeEx");
#endif

  bool _load_frame = true;

  do
    {
      //  Если буфер не был сформирован - вставляем задержку, чтобы не загружать систему.
      if (!_load_frame)
        {
          std::this_thread::sleep_for (std::chrono::microseconds (consts::mc_delay_skip_cycle));
        }

      _load_frame = false;

      {
        std::lock_guard<std::mutex> _grd (finfo_.src_mtx_);
        //  получен сигнал на выход - выходим.
        if (finfo_.stop_recv_)
          {
            return;
          }
        //  количество уже захваченных кадров больше или равно максимальному - переходим на засыпание.
        if (finfo_.lframes_.size () >= finfo_.capture_props_.count_preload_frame_)
          {
            XULOG_TRACE ("skip, exceed max count preloaded frames, " << finfo_.lframes_.size ());
            continue;
          }
        if (!finfo_.links_props_.pdriver2buff_)
          {
            XULOG_TRACE ("skip, finfo_.links_props_.pdriver2buff_ null");
            continue;
          }
        //  контроль частоты обработки кадров с данного устройства.
        if (!finfo_.capture_fps_.is_action ())
          {
            XULOG_TRACE ("skip, fps control");
            continue;
          }
      }

      XULOG_TRACE ("cycle load data from driver begin2");
      keys2buffs_ptr_type _new_buffs       = std::make_shared<gen_lib::keys2buffs_type> ();
      IVideoBuff::ptr     _gnew_buff       = finfo_.links_props_.pdriver2buff_->impl ()->get ();
      IVideoBuff::ptr     _gnew_codec_buff = finfo_.links_props_.pdriver2buff_->impl ()->get ();

      (*_new_buffs)[::utils::dbuffs::video::consts::offs::raw] = _gnew_buff;
      _gnew_buff->flush ();

      (*_new_buffs)[::utils::dbuffs::video::consts::offs::mjpg] = _gnew_codec_buff;
      _gnew_codec_buff->flush ();

      {
        transform_events_type _events_from_impl;

        if (finfo_.rdriver_.get ())
          {
            XULOG_TRACE ("try load data from driver");
            finfo_.rdriver_.get ()->get_raw_data (_new_buffs, &_events_from_impl);
          }

        for (auto& _key2buff : (*_new_buffs))
          {
            //  достаточно любого непустого буфера, чтобы произвести передачу всей структуры дальше.
            if (_key2buff.second && !_key2buff.second->get_flag (utils::dbuffs::TypeFlagsBuff::empty))
              {
                _load_frame = true;
                break;
              }
          }

        {
          std::lock_guard<std::mutex> _grd (finfo_.src_mtx_);

          if (_load_frame)
            {
              finfo_.lframes_.push_back (_new_buffs);
            }
          std::copy (_events_from_impl.begin (), _events_from_impl.end (), std::back_inserter (events_from_impl_));
          _events_from_impl.clear ();
          XULOG_TRACE ("_load_frame =" << to_str (_load_frame) << ", events_from_impl_.size=" << to_str (events_from_impl_.size ()));
        }
      }
    }
  while (true);
  return;
}


void
Filter::thread_postfunct_impl ()
{
  return;
}

}}}      // namespace dlls::sources::gen_vgen
