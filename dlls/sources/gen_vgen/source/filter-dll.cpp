//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_gen_vgen
\brief      Фильтр для создание видеопотока
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "mmedia/modules/uuu_log/appl/thread/exception-logger.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls { namespace sources { namespace gen_vgen {

using ExceptionLogger = ::modules::uuu_log::appl::thread::ExceptionLogger<::libs::link::ILink::ptr>;

ForeverLoadDlls Filter::freez_impls_;

Filter::Filter ()
{
  node_event2funct_[::libs::ievents::runtime::mem::BuffsEvent::gen_get_type_text_id ()] = [this](CallInterfInfo& _info) -> void {
    auto _devent = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::mem::BuffsEvent> (_info.event_);
    fill_buffer (&finfo_, _devent);
    return;
  };

  node_event2funct_[::libs::ievents::runtime::state::ChangStateProcessTypeEvent::gen_get_type_text_id ()] = [this](CallInterfInfo& _info) -> void {
    auto _event = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_info.event_);
    if (_event->is_start ())
      {
        update_driver (&finfo_);
      }
    else
      {
        if (finfo_.rdriver_.get ())
          {
            finfo_.rdriver_.get ()->stop ();
          }
      }
    return;
  };
}


Filter::~Filter ()
{}


void
Filter::load_int (FilterInfo* _info, const base_functs::xml::itn& _node)
{
  init_pts (&_info->pts_);

  finfo_.load (_node);

  auto _pdemons = ::libs::iproperties::helpers::cast_prop_demons ();
  auto _ibuff   = _pdemons->get_buffs_lockfree ()->impl ();
  auto _ioptim  = _pdemons->get_optim_lockfree ()->impl ();

  flip_y_      = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CFlipYAlg::val_key));
  finfo_.buff_ = _ibuff->get ();
  finfo_.capture_fps_.set_fps (UUU_ICAST_FLOAT (finfo_.capture_props_.capture_fps_));

  finfo_.recv_thread_.reset (
    new std::thread (
      ::libs::helpers::thread::generic_thread_funct<Filter, ExceptionLogger>,
      this,
      ExceptionLogger (::libs::link::ILink::ptr ()),
      UUU_ICAST_USHORT (0)));
  return;
}


void
Filter::transform_int (TransformInfo& _info)
{
  if (::libs::events::UsingStateEvent::disabled == finfo_.props_->get_using_state ())
    {
      return;
    }
  return;
}


void
Filter::call_int (CallInterfInfo& _info)
{
  super::prepare_call (_info);
  super::call_gen (_info);
  return;
}


IInterfPathObj::raw_ptr
Filter::query_int (const ::libs::helpers::utils::cuuid& _interf)
{
  if (_interf == ::libs::helpers::uids::interf::idata_source)
    {
      return &support_interf_;
    }
  if (_interf == ::libs::helpers::uids::interf::ctrl_driver_dshow)
    {
      return &support_interf_;
    }
  return nullptr;
}


void
Filter::init_pts (ConnectInfo* info)
{
  info->count_ins_  = 0;
  info->count_outs_ = 1;

  info->outs_[0].set_info (true);
  return;
}

}}}      // namespace dlls::sources::gen_vgen
