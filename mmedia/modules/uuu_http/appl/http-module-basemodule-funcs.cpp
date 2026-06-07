/**
\file       http-module-basemodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.08.2018
\project    u3_http_module
*/
#include "../module-http-includes_int.hpp"
#include "mmedia/dlls/terminals/video_sender/consts/video-sender-const-vals.hpp"
#include "http-module-syn.hpp"
#include "http-module.hpp"

namespace modules::uuu_http::appl
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
  const std::string name_data = "";
  auto              type_run  = ::libs::link::details::CodeRuns::appl;
  auto              lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();

  auto temp_link = lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      type_run,
      name_data,
      "mpl_uuu_http",
      appinfo.company_name_,
      appinfo.appl_name_,
      "subsys_http",
      ::libs::link::details::ModuleLinks::http,
      ::libs::link::consts::size::buf_appl2http));

  links_.set (syn::mids::http2appl, temp_link);

  //  Нужно установить свои связи в свойства разделяемые и спользовать их.
  {
    auto  proplinks = U3_CAST_PROP (syn::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    auto& links     = proplinks->update_links_lockfree ();

    links.set (syn::mids::http2appl, links_.get (syn::mids::http2appl));
    logger_ = links_.get (syn::mids::http2appl);
  }

  {
    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangDShowRunsSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::ilog_events::AppllPartLogInfo (
        ::libs::ievents::props::modules::log::LogLevels::info,
        ::modules::uuu_http::appl::consts::module_name,
        ::libs::helpers::log::get_module_version ()),
      "");

    props->set_start (true);
    links_.get (syn::mids::http2appl)->send_msg (rmsg, syn::CallSyncs::async, syn::Calls::set);
  }
}   // namespace modules::uuu_http::appl


void
HttpModule::init_proxys_int ()
{
  super::init_proxys_int ();
  U3_CHECK (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "check create block mem allocator");
}


bool
HttpModule::appl_deinit_int ()
{
  U3_XLOG_MARK ("HttpModule::deinit_int begin")
  if (links_.get (syn::mids::http2appl))
  {
    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangDShowRunsSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::ilog_events::AppllPartLogInfo (
        ::libs::ievents::props::modules::log::LogLevels::info,
        ::modules::uuu_http::appl::consts::module_name,
        ::libs::helpers::log::get_module_version ()),
      "");

    props->set_start (false);
    links_.get (syn::mids::http2appl)->send_msg (rmsg, syn::CallSyncs::async, syn::Calls::set);
  }

  {
    auto links = U3_CAST_PROP (syn::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    links->update_links_lockfree ().reset_link (syn::mids::http2appl);
  }

  links_.get (syn::mids::http2appl)->destroy ();
  links_.reset_link (syn::mids::http2appl);
  return true;
}


void
HttpModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[syn::ChangeStateProcessEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        U3_LOG_HTTP_DBG ("received " + syn::ChangeStateProcessEvent::gen_get_mid ());
        auto props = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (msg);
        U3_ASSERT (props);
        process_change_state_process (props);
        return syn::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::WrapperHttpEvent::gen_get_mid ()] =
    [] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        U3_LOG_HTTP_DBG ("received " + syn::WrapperHttpEvent::gen_get_mid ());
        return ::libs::iproperties::helpers::cast_event< syn::WrapperHttpEvent > (msg)->get_msg ();
      }
      return msg;
    };

  catch_funcs_[syn::ZipDataEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        U3_LOG_HTTP_DBG ("received " + syn::ZipDataEvent::gen_get_mid ());
        auto props = ::libs::iproperties::helpers::cast_event< syn::ZipDataEvent > (msg);
        U3_ASSERT (props);
        process_zip_data_event (props);
        return syn::IEvent::ptr ();
      }
      return msg;
    };
#ifdef U3_FAKE_DISABLE
  catch_funcs_[syn::RuntimeEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        U3_LOG_HTTP_DBG ("received " + syn::RuntimeEvent::gen_get_mid ());
        auto props = ::libs::iproperties::helpers::cast_event< syn::RuntimeEvent > (msg);
        U3_ASSERT (props);
        process_runtime (props);
        return syn::IEvent::ptr ();
      }
      return msg;
    };

  int_catch_funcs_[syn::MemResourceHttpEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      U3_LOG_HTTP_DBG ("received internal " + syn::MemResourceHttpEvent::gen_get_mid ());
      auto props = ::libs::iproperties::helpers::cast_event< syn::MemResourceHttpEvent > (msg);
      U3_ASSERT (props);
      process_mem_resource (props);
      return msg;
    };
#endif
}
}   // namespace modules::uuu_http::appl
