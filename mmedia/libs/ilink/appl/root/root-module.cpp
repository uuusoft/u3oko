/**
\file       root-module.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_ilink
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "root-module.hpp"

namespace libs::ilink::appl::root
{
RootModule::RootModule () :
  seqs_ ([] (const StateProcessEventExt& left, const StateProcessEventExt& right) { return left.id_seq_ < right.id_seq_; }),
  deinit_stage_ (DeInitStages::send_stop_msg2allmost_all),
  deinit_stage_counter_ (0),
  time_dump_status_ (boost::posix_time::microsec_clock::universal_time ())
{
}


RootModule::~RootModule ()
{
}


void
RootModule::init_proxys_int ()
{
  super::init_proxys_int ();
  U3_CHECK (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "instance mem block allocator");
}


void
RootModule::init_links_int (const ::libs::link::appl::InitApplication& info)
{
  auto       main_appl = ::libs::iproperties::helpers::cast_event< syn::ApplicationProp > (appl_event_props_.main_appl_properties_.get ());
  const auto type_run  = main_appl->is_single_process () ? ::libs::link::details::CodeRuns::dll : ::libs::link::details::CodeRuns::appl;
  auto       lproxy    = LinkCreatorProxy::instance ();
  auto       iproxy    = lproxy->impl ();
  auto       ipstorage = ::libs::iproperties::helpers::get_storage ();

  {
    auto temp_link = iproxy->get_connect (
      ::libs::link::CreateInfo (
        type_run,
        "uuu_appl.exe",
        "mpl_uuu_log",
        appl_info_.company_name_,
        appl_info_.appl_name_,
        "subsys_appl2log",
        ::libs::link::details::ModuleLinks::log,
        ::libs::link::consts::size::buf_all2log));

    links_.set (syn::mids::appl2log, temp_link);

    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangDShowRunsSubSysLogEvent > (rmsg);

      dmsg->change_appl_info (
        ::libs::ilog_events::AppllPartLogInfo (
          ::libs::ievents::props::modules::log::LogLevels::info,
          appl_info_.appl_name_,
          ::libs::helpers::log::get_module_version ()),
        "");

      dmsg->set_start (true);
      links_.get (syn::mids::appl2log)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
    }

    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateProcessEvent > (rmsg);
      dmsg->set_start (true);
      links_.get (syn::mids::appl2log)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
    }
  }

  {
    auto temp_link = iproxy->get_connect (
      ::libs::link::CreateInfo (
        type_run,
        "uuu_appl.exe",
        "mpl_u3_events",
        appl_info_.company_name_,
        appl_info_.appl_name_,
        "subsys_events",
        ::libs::link::details::ModuleLinks::events,
        ::libs::link::consts::size::buf_all2events));

    links_.set (syn::mids::appl2events, temp_link);

    syn::IEvent::ptr rmsg;
    auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateProcessEvent > (rmsg);

    dmsg->set_start (true);
    links_.get (syn::mids::appl2events)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }

  {
    auto temp_link = iproxy->get_connect (
      ::libs::link::CreateInfo (
        type_run,
        "uuu_appl.exe",
        "mpl_uuu_storage",
        appl_info_.company_name_,
        appl_info_.appl_name_,
        "subsys_storage",
        ::libs::link::details::ModuleLinks::storage,
        ::libs::link::consts::size::buf_appl2storage));

    links_.set (syn::mids::appl2storage, temp_link);

    syn::IEvent::ptr rmsg;
    auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateProcessEvent > (rmsg);

    dmsg->set_start (true);
    links_.get (syn::mids::appl2storage)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }

#if defined(U3_GUI_ENABLE)
  {
    auto temp_link = iproxy->get_connect (
      ::libs::link::CreateInfo (
        type_run,
        "uuu_appl.exe",
        "mpl_uuu_gui",
        company_name_,
        appl_name_,
        "subsys_gui",
        ::libs::link::details::ModuleLinks::gui,
        ::libs::link::consts::size::buf_appl2gul));

    links_.set (syn::mids::appl2gui, temp_link);
  }
#endif

  {
    auto temp_link = iproxy->get_connect (
      ::libs::link::CreateInfo (
        type_run,
        "uuu_appl.exe",
        "mpl_uuu_mdata",
        appl_info_.company_name_,
        appl_info_.appl_name_,
        "subsys_data",
        ::libs::link::details::ModuleLinks::mdata,
        ::libs::link::consts::size::buf_appl2data));

    links_.set (syn::mids::appl2mdata, temp_link);
  }

  {
    syn::IEvent::ptr rmsg;
    auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateProcessEvent > (rmsg);

    dmsg->set_start (true);

    auto temp_link = iproxy->get_connect (
      ::libs::link::CreateInfo (
        type_run,
        "uuu_appl.exe",
        "mpl_uuu_http",
        appl_info_.company_name_,
        appl_info_.appl_name_,
        "subsys_http",
        ::libs::link::details::ModuleLinks::http,
        ::libs::link::consts::size::buf_appl2http));

    links_.set (syn::mids::appl2http, temp_link);
    links_.get (syn::mids::appl2http)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }

  //  Разделяем созданные интерфейсы между всей системой через объект "свойства".
  {
    ::libs::properties::vers::links::ILinksProperty::links_type links;
    links.copy_links (links_);
    ipstorage->set_prop (
      ::libs::properties::consts::keys::links_property,
      std::make_shared< ::libs::properties::vers::links::ILinksProperty > (links));
  }

  {
    syn::TextExtCpu helper;
    auto            info_cpu = ::libs::iproperties::helpers::cast_event< syn::InfoCPUEvent > (appl_event_props_.info_cpu_);

    U3_LOG_APPL_MARK ("selected SIMD CPU : " + helper.get_text (info_cpu->get_cpu_type ()));
    U3_LOG_APPL_MARK ("count CPU: " + std::to_string (info_cpu->get_cpu_count ()));
    U3_LOG_APPL_MARK ("count working threads: " + std::to_string (::libs::optim::mcalls::get_count_work_threads_by_count_cpu (info_cpu->get_cpu_count ())));

    links_.get (syn::mids::appl2mdata)->send_msg (appl_event_props_.info_cpu_, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }
}


void
change_module_state (
  const RootModule::links_type::link_ptr_type& link,
  const std::string&                           name_appl,
  bool                                         state)
{
  if (!link)
  {
    return;
  }

  syn::IEvent::ptr rmsg;
  auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateProcessEvent > (rmsg);

#if 0
  dmsg->change_appl_info (
    ::libs::ilog_events::AppllPartLogInfo (
      ::libs::ievents::props::modules::log::LogLevels::info,
      name_appl,
      ::libs::helpers::log::get_module_version () ),
    "");
#endif

  dmsg->set_start (state);
  link->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
}


bool
RootModule::appl_deinit_int ()
{
  bool ret = false;

  switch (deinit_stage_)
  {
  case DeInitStages::send_stop_msg2allmost_all: {
    if (links_.get (syn::mids::appl2log))
    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangDShowRunsSubSysLogEvent > (rmsg);

      dmsg->change_appl_info (
        ::libs::ilog_events::AppllPartLogInfo (
          ::libs::ievents::props::modules::log::LogLevels::info,
          appl_info_.appl_name_,
          ::libs::helpers::log::get_module_version ()),
        "");

      dmsg->set_start (false);
      links_.get (syn::mids::appl2log)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
    }

    change_module_state (links_.get (syn::mids::appl2http), appl_info_.appl_name_, false);
    change_module_state (links_.get (syn::mids::appl2mdata), appl_info_.appl_name_, false);

#if defined(U3_GUI_ENABLE)
    change_module_state (links_.get (syn::mids::appl2gui), appl_name_, false);
    if (links_.get (syn::mids::appl2gui))
    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< ::libs::igui_events::events::ExitApplEvent > (rmsg);
      links_.get (syn::mids::appl2gui)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
    }
#endif

    change_module_state (links_.get (syn::mids::appl2events), appl_info_.appl_name_, false);
    change_module_state (links_.get (syn::mids::appl2storage), appl_info_.appl_name_, false);
    // std::this_thread::sleep_for (std::chrono::milliseconds (10 * 1000)); // debug
    deinit_stage_ = DeInitStages::wait_stop_data_module;
    U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
    deinit_stage_counter_ = 0;
    break;
  }
  case DeInitStages::wait_stop_data_module: {
    if (!links_.get (syn::mids::appl2mdata) || !links_.get (syn::mids::appl2mdata)->is_connected ())
    {
      links_.reset_link (syn::mids::appl2mdata);
#if defined(U3_GUI_ENABLE)
      deinit_stage_ = DeInitStages::wait_stop_gui_module;
#else
      deinit_stage_ = DeInitStages::wait_stop_storage_module;
#endif
      U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
      deinit_stage_counter_ = 0;
    }
    ++deinit_stage_counter_;
    break;
  }
#if defined(U3_GUI_ENABLE)
  case DeInitStages::wait_stop_gui_module: {
    if (!links_.get (syn::mids::appl2gui) || !links_.get (syn::mids::appl2gui)->is_connected ())
    {
      links_.reset_link (syn::mids::appl2gui);
      deinit_stage_         = DeInitStages::wait_stop_storage_module;
      deinit_stage_counter_ = 0;
    }
    break;
  }
#endif
  case DeInitStages::wait_stop_storage_module: {
    if (!links_.get (syn::mids::appl2storage) || !links_.get (syn::mids::appl2storage)->is_connected ())
    {
      links_.reset_link (syn::mids::appl2storage);
      deinit_stage_ = DeInitStages::wait_stop_events_module;
      U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
      deinit_stage_counter_ = 0;
    }
    break;
  }
  case DeInitStages::wait_stop_events_module: {
    if (!links_.get (syn::mids::appl2events) || !links_.get (syn::mids::appl2events)->is_connected ())
    {
      links_.reset_link (syn::mids::appl2events);
      deinit_stage_ = DeInitStages::send_stop_msg2log_module;
      U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
      deinit_stage_counter_ = 0;
    }
    break;
  }
  case DeInitStages::send_stop_msg2log_module: {
    if (links_.get (syn::mids::appl2log))
    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateProcessEvent > (rmsg);

      dmsg->set_start (false);
      links_.get (syn::mids::appl2log)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
    }

    deinit_stage_ = DeInitStages::wait_stop_log_module;
    U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
    deinit_stage_counter_ = 0;
    break;
  }
  case DeInitStages::wait_stop_log_module: {
    if (!links_.get (syn::mids::appl2log) || !links_.get (syn::mids::appl2log)->is_connected ())
    {
      links_.reset_link (syn::mids::appl2log);
      deinit_stage_ = DeInitStages::done;
      U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
      deinit_stage_counter_ = 0;
    }
    break;
  }
  case DeInitStages::done: {
    ret = true;
    U3_XLOG_MARK ("RootModule::deinit_int next stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)) + " after" + VTOLOG (deinit_stage_counter_) + PTR_TOLOG (this));
    deinit_stage_counter_ = 0;
    break;
  }
  default:
    U3_ASSERT_SIGNAL ("Unknown deinit stage" + VTOLOG (U3_CAST_UINT32_FORCE (deinit_stage_)));
    break;
  }
  return ret;
}


void
RootModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[::libs::events::ISeqEvent::gen_get_mid ()] = std::bind (
    &RootModule::seq_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  catch_funcs_[::libs::events::ISyncEvent::gen_get_mid ()] = std::bind (
    &RootModule::sync_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  catch_funcs_[::libs::events::IRequestEvent::gen_get_mid ()] = std::bind (
    &RootModule::request_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  catch_funcs_[::libs::events::IAnswerEvent::gen_get_mid ()] = std::bind (
    &RootModule::answer_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  catch_funcs_[syn::ApplicationProp::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) {
      if (forward)
      {
        auto main_appl = ::libs::iproperties::helpers::cast_event< syn::ApplicationProp > (appl_event_props_.main_appl_properties_);
        msg->copy (main_appl);
        return syn::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::InfoCPUEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) {
      if (forward)
      {
        auto info_cpu = ::libs::iproperties::helpers::cast_event< syn::InfoCPUEvent > (appl_event_props_.info_cpu_);
        if (process_state.request_)
        {
          msg->copy (info_cpu);
        }
        else if (!process_state.answer_)
        {
          syn::TextExtCpu helper;
          info_cpu->copy (msg.get ());
          U3_LOG_APPL_MARK ("updated cpu: " + helper.get_text (info_cpu->get_cpu_type ()) + " {" + std::to_string (info_cpu->get_cpu_count ()) + "}");
          links_.get (syn::mids::appl2mdata)->send_msg (msg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);

          const auto active_paths = paths_->get_path (::libs::iproperties::appl_paths::Paths::active_appl_module);
          helpers::save_event_to_json_file (active_paths, msg);
        }
        return syn::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[::libs::ievents::props::modules::log::PropertyLogModuleEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) {
      if (forward)
      {
        auto info_log = ::libs::iproperties::helpers::cast_event< ::libs::ievents::props::modules::log::PropertyLogModuleEvent > (appl_event_props_.module_log_);
        if (process_state.request_)
        {
          msg->copy (info_log);
        }
        else if (!process_state.answer_)
        {
          info_log->copy (msg.get ());
          ::libs::ievents::props::modules::log::g_log_level = ::libs::ievents::props::modules::log::from_raw_val (info_log->get_val (::libs::ievents::props::modules::log::LogVals::log_level));
          links_.get (syn::mids::appl2log)->send_msg (msg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);

          const auto active_paths = paths_->get_path (::libs::iproperties::appl_paths::Paths::active_appl_module);
          helpers::save_event_to_json_file (active_paths, msg);
        }
        return syn::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[::libs::ievents_events::events::WrapperEventsEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) {
      if (forward)
      {
        if (!process_state.answer_)
        {
          links_.get (syn::mids::appl2events)->send_msg (msg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
          // const auto active_paths = paths_->get_path (::libs::iproperties::appl_paths::Paths::active_appl_module);
          // helpers::save_event_to_file (active_paths, msg);
        }
        return syn::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[::libs::ievents::runtime::state::ExpandTimesEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) {
      if (forward)
      {
        auto res = links_.get (syn::mids::appl2mdata)->send_msg (msg, ::libs::link::details::CallSyncs::sync, ::libs::link::details::Calls::set);
        return syn::IEvent::ptr ();
      }
      return msg;
    };
}


::libs::link::ILink::ptr
RootModule::get_dest_link (syn::IEvent::ptr& msg)
{
  U3_ASSERT (!current_seq_.dest_);

  //  Самые частые сообщения к основному модулю, т.к. фактически через него общаются друг с другом все другие модули.
  if (::libs::iproperties::helpers::cast_event< ::libs::imdata_events::events::BaseDataEvent > (msg))
  {
    return links_.get (syn::mids::appl2mdata);
  }
  //  Далее идут сообщения логирования.
  if (::libs::iproperties::helpers::cast_event< ::libs::ilog_events::events::BaseLogEvent > (msg))
  {
    return links_.get (syn::mids::appl2log);
  }
  if (::libs::iproperties::helpers::cast_event< ::libs::istorage_events::events::BaseStorageEvent > (msg))
  {
    return links_.get (syn::mids::appl2storage);
  }
  if (::libs::iproperties::helpers::cast_event< ::libs::ievents_events::events::BaseEventsEvent > (msg))
  {
    return links_.get (syn::mids::appl2events);
  }
  if (::libs::iproperties::helpers::cast_event< ::libs::ihttp_events::events::BaseHttpEvent > (msg))
  {
    return links_.get (syn::mids::appl2http);
  }
#if defined(U3_GUI_ENABLE)
  if (::libs::iproperties::helpers::cast_event< ::libs::igui_events::events::BaseGUIEvent > (msg))
  {
    return links_.get (syn::mids::appl2gui);
  }
#endif
  return ::libs::link::ILink::ptr ();
}
}   // namespace libs::ilink::appl::root
