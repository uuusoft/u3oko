//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       log_module.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       23.07.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "storage-module.hpp"

namespace modules { namespace uuu_storage { namespace appl {

StorageModule::StorageModule ()
{
  text_id_module_ = ::libs::ilink::consts::id_storage;
}


StorageModule::~StorageModule ()
{}


void
StorageModule::init_int (const ::libs::link::appl::InitApplication& _info)
{
  super::init_int (_info);
  name_company_ = _info.name_company_;
  name_appl_    = _info.name_appl_;
  //check_process ();
  return;
}


void
StorageModule::init_proxys_int ()
{
  super::init_proxys_int ();
  CHECK_CALL (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "failed, alloc mem proxy");
  return;
}


void
StorageModule::init_done_int ()
{
  return;
}


void
StorageModule::init_links_int (const ::libs::link::appl::InitApplication& _info)
{
  const std::string         _name_data = "";
  const TypeRunCode         _type_run  = ::libs::link::details::TypeRunCode::appl;
  LinkCreatorProxy::raw_ptr _lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();
  volatile auto             _ipstorage = ::libs::iproperties::helpers::get_storage ();
  _ipstorage;

  {
    ::libs::link::CreateInfo _create_info (
      _type_run,
      _name_data,
      "mpl_uuu_storage",
      _info.name_company_,
      _info.name_appl_,
      "subsys_storage",
      ::libs::link::details::TypeLinkModules::storage,
      ::libs::link::consts::size::buff_appl2storage);

    links_.storage2appl_ = _lproxy->impl ()->get_listen (&_create_info);
  }
  //  Нужно установить свои связи в свойства разделяемые и спользовать их.
  {
    auto  _proplinks    = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    auto& _links        = _proplinks->update_links_lockfree ();
    auto  _storage2appl = links_.storage2appl_;

    _links.storage2appl_ = _storage2appl;
    logger_              = _storage2appl;
  }
  return;
}


::libs::ilink::appl::base::BaseModule::recv_links_type
StorageModule::get_recv_link ()
{
  recv_links_type _ret;
  _ret.push_back (links_.storage2appl_);
  return _ret;
}


bool
StorageModule::catch_event (IEvent::ptr _evnt)
{
  return true;
}


bool
StorageModule::is_now_sleep_thread (bool _now_recv_evnt)
{
  return _now_recv_evnt ? false : true;
}


bool
StorageModule::deinit_int ()
{
  XULOG_INFO ("StorageModule::deinit_int: beg");

  {
    auto _links = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    _links->update_links_lockfree ().log2appl_.reset ();
  }

  links_.storage2appl_->destroy ();
  links_.storage2appl_.reset ();
  XULOG_INFO ("StorageModule::deinit_int: end");
  return true;
}

}}}      // namespace modules::uuu_storage::appl
