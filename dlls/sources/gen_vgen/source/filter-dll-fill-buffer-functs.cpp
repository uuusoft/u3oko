//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-fill-buffer-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_gen_vgen
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace sources { namespace gen_vgen {

void
Filter::fill_buffer (InfoFilter* _finfo, BuffsEvent::raw_ptr _event)
{
  XULOG_TRACE ("Filter::fill_buffer: beg");
  ::libs::buffs::Buffs::raw_ptr _buffs = _event->get_buff ().get ();

  _buffs->set_flag (::libs::buffs::TypeBuffsFlags::empty, true);

  std::lock_guard<std::mutex> _grd (_finfo->src_mtx_);

  if (_finfo->lframes_.empty ())
    {
      XULOG_TRACE ("Filter::fill_buffer: lframes empty, skip");
      return;
    }
  {
    bool  _set_raw_as_base = false;
    auto& _front           = *_finfo->lframes_.front ();

    _buffs->set_flag (::libs::buffs::TypeBuffsFlags::empty, false);

    for (auto& _keybuff : _front)
      {
        _buffs->set_buff (_keybuff.first, _keybuff.second);

        if (!_keybuff.second || _keybuff.second->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
          {
            continue;
          }
        //  Сырой (не пустой) буфер имеет приоритет.
        if (!_set_raw_as_base)
          {
            _buffs->set_indx_base_buff (_keybuff.first);
            _set_raw_as_base = utils::dbuffs::video::consts::offs::raw == _keybuff.first ? true : false;
          }
      }
  }

  //::libs::buffs::dump (_buffs, true);      //  debug
  _finfo->lframes_.pop_front ();

  if (!events_from_impl_.empty ())
    {
      auto _events = _event->get_events ();
      UASSERT (_events);
      std::copy (events_from_impl_.begin (), events_from_impl_.end (), std::back_inserter (*_events));
      events_from_impl_.clear ();

      for (const auto& _event : *_events)
        {
          auto _devent = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::interf::InterfCaptureImageEvent> (_event);
          if (_devent)
            {
              finfo_.active_impl_ = _devent->is_active () ? _devent->get_interface () : _finfo->null_impl_;
              UASSERT (!finfo_.active_impl_.expired ());
              finfo_.active_impl_.lock ()->update_property (&_finfo->capture_props_);
            }
        }
      XULOG_TRACE ("Filter::fill_buffer: _events.size=" << _events->size ());
    }
  XULOG_TRACE ("Filter::fill_buffer: end");
  return;
}


void
Filter::update_driver_exact (InfoFilter* _finfo, const std::string& _name_impl)
{
  UASSERT (!_name_impl.empty ());
  std::lock_guard<std::mutex> _grd (_finfo->src_mtx_);

  _finfo->rdriver_.init (_name_impl);

  auto _lib    = _finfo->rdriver_.get_lib ();
  auto _driver = _finfo->rdriver_.get ();
  CHECK_STATE (_lib, "failed, empty lib");
  CHECK_STATE (_driver, "failed, empty driver");

  freez_impls_.add (_name_impl, _lib);

  _driver->init ();

  auto _pdemons = ::libs::iproperties::helpers::cast_prop_demons ();

  _finfo->links_props_.pdriver2buff_ = _pdemons->get_buffs_lockfree ();
  _finfo->links_props_.pdriver2mem_  = _pdemons->get_mem_lockfree ();

  UASSERT (_finfo->links_props_.pdriver2buff_);
  UASSERT (_finfo->links_props_.pdriver2mem_);

  _driver->update_dinfo (gen_lib::SourceInfo (_finfo->rprops_, &_finfo->capture_props_, &_finfo->links_props_));
  _driver->start ();
  return;
}


void
Filter::update_driver (InfoFilter* _finfo)
{
  //  Тут обработчик исключения, т.к. одно исключение допустимо для переключения на фейковый драйвер в нормальной ситуации.
  try
    {
      update_driver_exact (_finfo, _finfo->rprops_->name_impl_dll_);
      //update_dshow_cpu ( _finfo );
      return;
    }
  catch (std::exception& _e)
    {
      DATA_EXCEPT_LOG (_e.what ());
    }

  //  у фальшивого драйвера все всегда должно быть нормально.
  update_driver_exact (_finfo, "vss_fake_vgen");
  //update_dshow_cpu ( _finfo );
  return;
}

}}}      // namespace dlls::sources::gen_vgen
