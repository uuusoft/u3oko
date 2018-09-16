//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       data-module.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_module_data
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "data-module.hpp"

namespace modules { namespace uuu_mdata { namespace appl {

DataModule::DataModule ()
{
  text_id_module_ = ::libs::ilink::consts::id_data;
}


DataModule::~DataModule ()
{}


void
DataModule::init_int (const ::libs::link::appl::InitApplication& _info)
{
  XULOG_TRACE ("DataModule::init_int: beg");
  super::init_int (_info);

  name_company_ = _info.name_company_;
  name_appl_    = _info.name_appl_;

  CHECK_CALL (check_process (), "failed, check_process");
  icore_ = ::libs::icore::create ();
  XULOG_TRACE ("DataModule::init_int: end");
  return;
}


void
DataModule::init_proxys_int ()
{
  super::init_proxys_int ();
  return;
}


void
DataModule::init_links_int (const ::libs::link::appl::InitApplication& _info)
{
  XULOG_TRACE ("DataModule::init_links_int: beg");
  const RunCodeType         _type_run  = RunCodeType::appl;
  LinkCreatorProxy::raw_ptr _lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();
  volatile auto             _ipstorage = ::libs::iproperties::helpers::get_storage ();

  _ipstorage;

  {
    XULOG_INFO ("make appl link");
    ::libs::link::CreateInfo _create_info (
      _type_run,
      std::string (""),
      "mpl_uuu_mdata",
      _info.name_company_,
      _info.name_appl_,
      "subsys_data",
      ::libs::link::details::LinkModulesType::mdata,
      ::libs::link::consts::size::buff_appl2data);

    links_.data2appl_ = _lproxy->impl ()->get_listen (&_create_info);
  }
  //  нужно установить свои связи в свойства разделяемые и спользовать их.
  {
    auto _links                                 = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    _links->update_links_lockfree ().data2appl_ = links_.data2appl_;
  }

  logger_ = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().data2appl_.lock ();

  IEvent::ptr _rmsg;
  auto        _props = ::libs::iproperties::helpers::get_and_cast_event<::libs::ilog_events::events::ChangStateProcessTypeSubSysLogEvent> (_rmsg);
  _props->update_info (::libs::ilog_events::AppllPartLogInfo (::modules::uuu_mdata::appl::consts::name_application, __FILE__, __LINE__), "");

  _props->set_start (true);
  links_.data2appl_->send_msg (_rmsg);
  XULOG_TRACE ("DataModule::init_links_int: end");
  return;
}


::libs::ilink::appl::base::BaseModule::recv_links_type
DataModule::get_recv_link ()
{
  recv_links_type _ret;
  _ret.push_back (links_.data2appl_);
  return _ret;
}


bool
DataModule::catch_event (IEvent::ptr _evnt)
{
  return true;
}


bool
DataModule::is_now_sleep_thread (bool _now_recv_evnt)
{
  return _now_recv_evnt ? false : true;
}


void
DataModule::update_catch_functs_int ()
{
  super::update_catch_functs_int ();

  catch_functs_[FrameDone::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[InfoCPUEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _props = ::libs::iproperties::helpers::cast_event<InfoCPUEvent> (_msg);
        UASSERT (_props);
        process_info_cpu (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[ChangePathsDataEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _props = ::libs::iproperties::helpers::cast_event<ChangePathsDataEvent> (_msg);
        UASSERT (_props);
        process_change_paths_data (_props);
        return IEvent::ptr ();
      }

    return _msg;
  };

  catch_functs_[ListDevicesDataEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        UASSERT_SIGNAL ("unimplemented");
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[ListXmlFilesDataEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _props = ::libs::iproperties::helpers::cast_event<ListXmlFilesDataEvent> (_msg);
        UASSERT (_props);
        process_list_xml_files (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[GetNodesDataEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _props = ::libs::iproperties::helpers::cast_event<GetNodesDataEvent> (_msg);
        UASSERT (_props);
        process_get_nodes (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[ChangeNodeDataEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _props = ::libs::iproperties::helpers::cast_event<ChangeNodeDataEvent> (_msg);
        UASSERT (_props);
        process_change_node (_props, _msg);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[ExpandTimeStatisticEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        DATA_LOG ("catch ::libs::ievents::runtime::state::ExpandTimeStatisticEvent");
        auto _props = ::libs::iproperties::helpers::cast_event<ExpandTimeStatisticEvent> (_msg);
        UASSERT (_props);
        process_expand_time_statistic (_props, _msg);
        return IEvent::ptr ();
      }
    return _msg;
  };

  return;
}


bool
DataModule::deinit_int ()
{
  XULOG_INFO ("DataModule::deinit_int: beg");
  if (links_.data2appl_)
    {
      XULOG_INFO ("DataModule::deinit_int: send msg 2 log about stop");
      IEvent::ptr _rmsg;
      auto        _props = ::libs::iproperties::helpers::get_and_cast_event<::libs::ilog_events::events::ChangStateProcessTypeSubSysLogEvent> (_rmsg);
      _props->update_info (::libs::ilog_events::AppllPartLogInfo (::modules::uuu_mdata::appl::consts::name_application, __FILE__, __LINE__), "");
      _props->set_start (false);
      links_.data2appl_->send_msg (_rmsg);
    }

  for (auto& _val : idatas_)
    {
      ptr_path_type& _path = _val.second;
      if (_path.expired ())
        {
          continue;
        }

      XULOG_INFO ("DataModule::deinit_int: prepare stop path");
      stop_path (_val.first);
      CHECK_CALL_NO_THROW (icore_->delete_path (_path));
      _path.reset ();
    }

  XULOG_INFO ("DataModule::deinit_int: all paths stop");
  icore_.reset ();

  {
    auto _links = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    _links->update_links_lockfree ().data2appl_.reset ();
  }

  links_.data2appl_->destroy ();
  links_.data2appl_.reset ();
  XULOG_INFO ("DataModule::deinit_int: end");
  return true;
}


bool
DataModule::check_process ()
{
  sys_info_ = ::libs::helpers::sys::get_impl ();
  return true;
}

}}}      // namespace modules::uuu_mdata::appl
