/**
\file       http-module-basemodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.08.2018
\project    mhttp
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../module-http-includes_int.hpp"
#include "mmedia/dlls/terminals/video_sender/consts/video-sender-const-vals.hpp"
#include "http-module-syn.hpp"
#include "http-module.hpp"

namespace modules::mhttp::appl
{
void
HttpModule::appl_init_int (const syn::InitApplication& appinfo)
{
  super::appl_init_int (appinfo);
  check_process ();
}


void
HttpModule::init_links_int (const syn::InitApplication& appinfo)
{
  U3_XLOG_DBG ("HttpModule::init_links_int::---->");
  const std::string name_data = "";
  auto              type_run  = ::libs::link::details::CodeRuns::appl;
  auto              lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();

  auto temp_link = lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      type_run,
      name_data,
      "mpl_mhttp",
      appinfo.company_name_,
      appinfo.appl_name_,
      "subsys_http",
      ::libs::link::details::ModuleLinks::http,
      ::libs::link::consts::sizes::buf_appl2http));

  links_.set (syn::mids::http2appl, temp_link);

  //  Нужно установить свои связи в свойства разделяемые и спользовать их.
  {
    auto* proplinks = ::libs::iproperties::helpers::get_prop_links ();
    auto& links     = proplinks->update_links_lockfree ();

    links.set (syn::mids::http2appl, links_.get (syn::mids::http2appl));
    logger_ = links_.get (syn::mids::http2appl);
  }

  {
    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangeStateSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::events_log::AppllPartLogInfo (
        ::libs::events_base::props::modules::log::LogLevels::info,
        ::modules::mhttp::appl::consts::module_name,
        ::libs::utility::log::get_module_version ()),
      "");

    props->set_start (true);
    links_.get (syn::mids::http2appl)->send_msg (rmsg, syn::CallSyncs::async, syn::Calls::set);
  }
  U3_XLOG_DBG ("HttpModule::init_links_int::<----");
}


void
HttpModule::init_proxys_int ()
{
  super::init_proxys_int ();
  U3_CHECK (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "check create block mem allocator");
}


auto
HttpModule::appl_deinit_int () -> bool
{
  U3_XLOG_MARK ("HttpModule::deinit_int::---->")
  if (links_.get (syn::mids::http2appl))
  {
    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangeStateSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::events_log::AppllPartLogInfo (
        ::libs::events_base::props::modules::log::LogLevels::info,
        ::modules::mhttp::appl::consts::module_name,
        ::libs::utility::log::get_module_version ()),
      "");

    props->set_start (false);
    links_.get (syn::mids::http2appl)->send_msg (rmsg, syn::CallSyncs::async, syn::Calls::set);
  }

  {
    auto* links = ::libs::iproperties::helpers::get_prop_links ();
    links->update_links_lockfree ().reset_link (syn::mids::http2appl);
  }

  links_.get (syn::mids::http2appl)->destroy ();
  links_.reset_link (syn::mids::http2appl);
  U3_XLOG_MARK ("HttpModule::deinit_int::<----")
  return true;
}


void
HttpModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[syn::ChangeStateProcessEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      U3_LOG_HTTP_DBG ("int received " + syn::ChangeStateProcessEvent::gen_get_mid ());
      auto* props = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (msg);
      U3_ASSERT (props);
      process_change_state_process (props);
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::WrapperHttpEvent::gen_get_mid ()] =
    [] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      U3_LOG_HTTP_DBG ("int received " + syn::WrapperHttpEvent::gen_get_mid ());
      return ::libs::iproperties::helpers::cast_event< syn::WrapperHttpEvent > (msg)->get_msg ();
    }
    return msg;
  };

  catch_funcs_[syn::ZipDataEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      U3_LOG_HTTP_DBG ("int received " + syn::ZipDataEvent::gen_get_mid ());
      auto* props = ::libs::iproperties::helpers::cast_event< syn::ZipDataEvent > (msg);
      U3_ASSERT (props);
      process_zip_data_event (props);
      return syn::IEvent::ptr ();
    }
    return msg;
  };
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  catch_funcs_[syn::RuntimeEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        U3_LOG_HTTP_DBG ("int received " + syn::RuntimeEvent::gen_get_mid ());
        auto* props = ::libs::iproperties::helpers::cast_event< syn::RuntimeEvent > (msg);
        U3_ASSERT (props);
        process_runtime (props);
        return syn::IEvent::ptr ();
      }
      return msg;
    };

  int_catch_funcs_[syn::MemResourceHttpEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      U3_LOG_HTTP_DBG ("int received " + syn::MemResourceHttpEvent::gen_get_mid ());
      auto* props = ::libs::iproperties::helpers::cast_event< syn::MemResourceHttpEvent > (msg);
      U3_ASSERT (props);
      process_mem_resource (props);
      return msg;
    };
#endif
}
}   // namespace modules::mhttp::appl
