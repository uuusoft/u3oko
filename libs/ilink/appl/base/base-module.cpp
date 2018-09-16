//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-module.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes_int.hpp"
#include "base-module.hpp"

namespace libs { namespace ilink { namespace appl { namespace base {

BaseModule::BaseModule () :
  ms_time_sleep_ (::libs::link::consts::wait_delay_recv_msg_ms),
  name_appl_ (""),
  txt_ver_ ("0.0.0"),
  name_company_ ("uuusoft"),
  sys_info_ (nullptr),
  all2mem_ (nullptr),
  all2buff_ (nullptr),
  all2optim_ (nullptr),
  all2events_ (nullptr),
  text_id_module_ ("uuu_unknown_module"),
  stop_module_ (false)
{
  register_events_for_module ();
}


BaseModule::~BaseModule ()
{}


void
BaseModule::init_int (const ::libs::link::appl::InitApplication& _info)
{
  sys_info_ = ::libs::helpers::sys::get_impl ();
  return;
}


void
BaseModule::init_appl_folders_int ()
{
  UASSERT (!name_company_.empty ());
  UASSERT (!name_appl_.empty ());
  paths_ = std::make_shared<::libs::iproperties::appl_paths::AppPaths> ();
  paths_->load (name_company_, name_appl_, txt_ver_);
  return;
}


void
BaseModule::init_appl_data_int ()
{
  XULOG_TRACE ("uuu_soft::BaseModule::load_appl_data::beg");
  load_events_props ();
  update_events_props ();
  XULOG_TRACE ("uuu_soft::BaseModule::load_appl_data::end");
  return;
}


void
BaseModule::init_proxys_int ()
{
  all2mem_    = BlockMemAllocatorProxy::instance (paths_->get_path (TypePath::bins));
  all2buff_   = utils::dbuffs::allocator::BuffAllocatorProxy::instance (paths_->get_path (TypePath::bins));
  all2optim_  = ::libs::optim::io::IOptimProxy::instance (paths_->get_path (TypePath::bins));
  all2events_ = ::libs::events::io::IEventsProxy::instance (paths_->get_path (TypePath::bins));

  CHECK_STATE (all2mem_, "failed, null all2mem");
  CHECK_STATE (all2buff_, "failed, empty all2buff");
  CHECK_STATE (all2optim_, "failed, null all2optim");
  CHECK_STATE (all2events_, "failed, null all2events");

  {
    IDemonsProperty::raw_ptr    _orinfo = ::libs::iproperties::helpers::cast_prop_demons ();
    ISharedProperty::guard_type _guard (_orinfo->get_sync ());

    _orinfo->set_buffs_lockfree (all2buff_);
    _orinfo->set_mem_lockfree (all2mem_);
    _orinfo->set_optim_lockfree (all2optim_);
    _orinfo->set_events_lockfree (all2events_);
  }
  return;
}


void
BaseModule::init_done_int ()
{
  return;
}


void
BaseModule::update_catch_functs_int ()
{
  return;
}


void BaseModule::force_stop_int ()
{
  stop_module_ = true;
  return;
}

}}}}      // namespace libs::ilink::appl::base
