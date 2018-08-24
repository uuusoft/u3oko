//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       path-local-thread-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../includes_int.hpp"
#include "../includes.hpp"
#include "path.hpp"
#include "mmedia/libs/helpers/statistic/helpers/functors_with_statistic.hpp"

namespace libs { namespace icore { namespace impl { namespace var1 { namespace path {
//  syn
using transform_events_type = var1::obj::dll::TransformInfo::events_type;

void
Path::thread_funct_impl (std::size_t _indx_thread)
{
  bool        _working         = true;
  std::size_t _frames_no_sleep = 0;
  bool        _sleep_now       = false;
  int         _ms_sleep        = path::consts::ms_sleep_work_thread_soft;

  do
    {
      bool _pres = false;

      {
        guard_type _grd (ctrl_mtx_);
        _working = req_terminate_thread_ ? false : true;
        _pres    = process_impl ();
      }

      if (!_working)
        {
          XULOG_TRACE ("Path::thread_funct_impl: stop working");
          break;
        }

      ++_frames_no_sleep;
      //  Если мы не обработали не одного буфера или превышено ммаксимальное количество обработанных буферов без засыпания - засыпаем.
      //  избегаем возможного замедления других подсистем на одноядерной машине.
      _sleep_now = false;

      if (!_pres)
        {
          _sleep_now = true;
          _ms_sleep  = path::consts::ms_sleep_work_thread_soft;
        }
      if (_pres && _frames_no_sleep > path::consts::max_count_frames_without_sleep)
        {
          _sleep_now = true;
          _ms_sleep  = path::consts::ms_sleep_work_thread_force;
        }
      if (_sleep_now)
        {
          //std::this_thread::yield ();
          std::this_thread::sleep_for (std::chrono::milliseconds (_ms_sleep));
          _frames_no_sleep = 0;
        }
    }
  while (true);
  return;
}


void
Path::thread_postfunct_impl ()
{
  return;
}


bool
Path::process_impl ()
{
  if (obj::RunStateFilter::run != state_)
    {
      XULOG_TRACE ("Path::process_impl: not running, skip");
      return false;
    }

  if (!work_buffs_)
    {
      work_buffs_ = std::make_shared<::libs::buffs::Buffs> ();
    }

  bool                  _ret                = true;
  int                   _count_filled_buffs = 0;
  const std::size_t     _count_source       = source_interf_objs_[path::consts::indx_source_interf_helper];
  transform_events_type _frame_events;      //< Список событий, которые произошли на данный момент при обработке данного фрейма (кадр, буфер) данных.
  IEvent::ptr           _rmsg;
  auto                  _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::mem::BuffsEvent> (_rmsg);

  _dmsg->set_buff (work_buffs_);
  _dmsg->set_events (&_frame_events);

  for (std::size_t _sindx = 0; _sindx < _count_source; ++_sindx)
    {
      const auto& _ssource = interf_objs_[path::consts::indx_source_interf_helper];
      auto        _source  = _ssource[_sindx].get ();
      auto        _lsource = dynamic_cast<var1::obj::ObjPath::raw_ptr> (_source);
      //  Начинаем от объекта источника проходим по всем точкам соедининия и рекурсивно вызываем для каждого последующего
      //  фильтра функцию обработки
      work_buffs_->set_flag (::libs::buffs::TypeBuffsFlags::empty, true);

      {
        //  собираем статистику по источникам отдельно от остальныхю
        AddTimeStatistic _stat_grd (expand_objs_time_, _lsource->name_lib_);

        XULOG_TRACE ("Path::process_impl: prepare send event to source");
        _source->send_event2me (_rmsg);

        if (!work_buffs_->get_flag (::libs::buffs::TypeBuffsFlags::empty))
          {
            ++_count_filled_buffs;
          }
        else
          {
            _stat_grd.change_name (_lsource->name_lib_ + ".empty");
          }
      }

      if (!work_buffs_->get_flag (::libs::buffs::TypeBuffsFlags::empty))
        {
          XULOG_TRACE ("Path::process_impl: received filling buffer");
          XULOG_TRACE ("Path::process_impl: _frame_events.size=" << _frame_events.size ());
          //  Если есть заполненный буфер надо его обработать - вызывая рекурсивно функцию обработки для всей цепочки фильтров -
          //  получаем заполненный буфер данных.
          work_funct_impl (_lsource, work_buffs_, _lsource->info_.pts_.outs_[0].indx_pt_, &_frame_events);
          //  Передаем связанные с данным кадром события (если они есть) в общую подсистему обработки событий.
          if (!_frame_events.empty ())
            {
              auto _ievents = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().data2appl_.lock ();
              UASSERT (_ievents);

              for (auto& _fevent : _frame_events)
                {
                  if (::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::interf::BaseInterfEvent> (_fevent))
                    {
                      //  Все интерфейсные сообщения являются локальными для данного графа обработки данных.
                      continue;
                    }
                  _ievents->send_msg (_fevent);
                }

              _frame_events.clear ();
            }
        }

    }      //end for

  count_process_frames_ += _count_filled_buffs;
  XULOG_TRACE ("Path::process_impl: end, count process frames=" << _count_filled_buffs);
  return _count_filled_buffs ? _ret : false;
}


void
Path::work_funct_impl (
  var1::obj::ObjPath::raw_ptr _pfilter,
  ::libs::buffs::Buffs::ptr&  _ibuffs,
  const unsigned int          _iindx,
  events_type*                _frame_events)
{
  if (!_pfilter)
    {
      //  Допустимая ситуация, конечный фильтр не имеет последующего, что очевидно.
      return;
    }

  const auto& _finfo = _pfilter->get_info ();
  //  Проходим по всем выходным точкам данного фильтра и для каждого фильтра связанного с ней вызываем рекусрисвно данную функцию.
  //  Точек может и не быть, но один раз выполнять работу мы должны в любом случае.
  const int _count_outs = _finfo.pts_.count_outs_;
  for (int _oindx = 0; _oindx < _count_outs; ++_oindx)
    {
      const auto& _out_pt = _finfo.pts_.outs_[_oindx];

      if (!_out_pt.active_)
        {
          continue;
        }

      //  По умолчанию вход совпадает с выходом, вся обработка ведется на месте. Это поведение может быть изменено фильтром.
      ::libs::buffs::Buffs::ptr _obuffs = _ibuffs;
      //  Вызываем функцию преобразования для данного фильтра при этом фильтр должен сформировать таблицу флагов, указывающих
      //  по каким соединенным выходным точкам следует пересылать данные
      {
        obj::dll::TransformInfo _cinfo (&_ibuffs, &_obuffs, 0, _iindx, _oindx, _frame_events);
        AddTimeStatistic        _stat_grd (expand_objs_time_, _pfilter->name_lib_);

        XULOG_TRACE ("--->Path::work_funct_impl: beg send buffer to filter: " << _pfilter->name_lib_);
        //::libs::buffs::dump (_ibuffs.get ());      //  debug
        _pfilter->transform (_cinfo);
        XULOG_TRACE ("<---Path::work_funct_impl: end send buffer to filter: " << _pfilter->name_lib_);
      }

      if (_oindx < _count_outs)
        {
          work_funct_impl (_out_pt.filter_, _obuffs, _out_pt.indx_pt_, _frame_events);
        }
    }
  return;
}

}}}}}      // namespace libs::icore::impl::var1::path
