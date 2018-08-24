//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       log_module.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "log-module.hpp"

namespace modules { namespace uuu_log { namespace appl {

LogModule::LogModule () :
  indx_file_ (0)
{
  text_id_module_ = ::libs::ilink::consts::id_log;
}


LogModule::~LogModule ()
{}


void
LogModule::init_int (const ::libs::link::appl::InitApplication& _info)
{
  super::init_int (_info);

  name_company_ = _info.name_company_;
  name_appl_    = _info.name_appl_;
  check_process ();
  return;
}


void
LogModule::init_proxys_int ()
{
  //super::init_proxys_int();
  CHECK_CALL (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "failed, alloc mem proxy");
  return;
}


void
LogModule::init_done_int ()
{
  make_dir_for_logs ();
  open_log_file ();
  return;
}


void
LogModule::init_links_int (const ::libs::link::appl::InitApplication& _info)
{
  const std::string         _name_data = "";
  const TypeRunCode         _type_run  = ::libs::link::details::TypeRunCode::appl;
  LinkCreatorProxy::raw_ptr _lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();
  volatile auto             _ipstorage = ::libs::iproperties::helpers::get_storage ();
  volatile auto             _imstorage = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ();

  _ipstorage;
  _imstorage;

  {
    ::libs::link::CreateInfo _create_info (
      _type_run,
      _name_data,
      "mpl_uuu_log",
      _info.name_company_,
      _info.name_appl_,
      "subsys_appl2log",
      ::libs::link::details::TypeLinkModules::log,
      ::libs::link::consts::size::buff_all2log);

    links_.log2appl_ = _lproxy->impl ()->get_listen (&_create_info);
  }
  //  нужно установить свои связи в свойства разделяемые и спользовать их.
  {
    auto  _proplinks = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    auto& _links     = _proplinks->update_links_lockfree ();
    auto  _log2appl  = links_.log2appl_;

    _links.log2appl_ = _log2appl;
    logger_          = _log2appl;
  }
  return;
}


::libs::ilink::appl::base::BaseModule::recv_links_type
LogModule::get_recv_link ()
{
  recv_links_type _ret;

  _ret.push_back (links_.log2appl_);
  return _ret;
}


bool
LogModule::catch_event (IEvent::ptr _evnt)
{
  return true;
}


bool
LogModule::is_now_sleep_thread (bool _now_recv_evnt)
{
  auto _log_prop = ::libs::iproperties::helpers::cast_event<::libs::ievents::props::modules::log::PropertyLogModuleEvent> (event_props_.module_log_);
  if (events_.size () > _log_prop->get_val (ValsLogModule::max_cache_events))
    {
      flush_events ();
    }

  return _now_recv_evnt ? false : true;
}


bool
LogModule::deinit_int ()
{
  XULOG_INFO ("LogModule::deinit_int: beg");
  flush_events ();

  {
    auto _links = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    _links->update_links_lockfree ().log2appl_.reset ();
  }

  links_.log2appl_->destroy ();
  links_.log2appl_.reset ();
  XULOG_INFO ("LogModule::deinit_int: end");
  return true;
}


void
LogModule::check_process ()
{
  return;
}


void
LogModule::add_msg_from_self (const std::string& _info)
{
  UASSERT (!_info.empty ());
  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<levents::InfoLogEvent> (_rmsg);
  _dmsg->update_info (::libs::ilog_events::AppllPartLogInfo ("uuu_log"), _info);
  events_.push_back (_rmsg);
  return;
}

}}}      // namespace modules::uuu_log::appl
