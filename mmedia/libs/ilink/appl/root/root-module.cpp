/**
\file       root-module.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_ilink
*/
// #define U3_USE_DEB_LOG_LEVEL
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
        "mappl.exe",
        "mpl_mlog",
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
        "mappl.exe",
        "mpl_mevents",
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
        "mappl.exe",
        "mpl_mstorage",
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

#ifdef U3_GUI_ENABLE
  {
    auto temp_link = iproxy->get_connect (
      ::libs::link::CreateInfo (
        type_run,
        "mappl.exe",
        "mpl_mgui",
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
        "mappl.exe",
        "mpl_mdata",
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
        "mappl.exe",
        "mpl_mhttp",
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
#ifdef U3_GUI_ENABLE
  if (::libs::iproperties::helpers::cast_event< ::libs::igui_events::events::BaseGUIEvent > (msg))
  {
    return links_.get (syn::mids::appl2gui);
  }
#endif
  return ::libs::link::ILink::ptr ();
}


syn::IEvent::ptr
RootModule::default_catch_func (
  syn::IEvent::ptr&           msg,
  bool                        forward,
  const StateProcessEventExt& process_state)
{
  try
  {
    if (forward)
    {
      //  Если сообщение уже пришло с транзакцией, значит это ответ на нашу транзакцию.
      if (current_seq_.recv_seq_)
      {
        U3_ASSERT (current_seq_.answer_);
        return syn::IEvent::ptr ();
      }

      U3_ASSERT (!current_seq_.dest_);
      current_seq_.dest_ = get_dest_link (msg);   //  Ищем модуль будет обрабатывать данное сообщение и, если модуль существует, помечаем сообщение для транзакции.

      if (current_seq_.dest_ && (current_seq_.sync_event_ || current_seq_.request_))
      {
        //  инициируем новую транзакцию.
        current_seq_.make_seq_ = true;
        current_seq_.id_seq_   = boost::uuids::random_generator () ();
        // U3_XLOG_DEV ("catch seq msg " << current_seq_.id_seq_.name ());
      }

      return syn::IEvent::ptr ();
    }
  }
  catch (const std::exception& e)
  {
    U3_XLOG_ERROR ("RootModule::default_catch_func" + TOLOG (text_id_module_) + std::string (e.what ()) + TOLOG (msg->get_mid ()));
  }
  return syn::IEvent::ptr ();
}


syn::IEvent::ptr
RootModule::seq_msg_catch_func (
  syn::IEvent::ptr&           msg,
  bool                        forward,
  const StateProcessEventExt& process_state)
{
  if (forward)
  {
    auto seq_ret = ::libs::iproperties::helpers::cast_event< ::libs::events::ISeqEvent > (msg);
    auto ret     = seq_ret->get_msg ();

    U3_ASSERT (ret);
    current_seq_.recv_seq_ = true;
    current_seq_.id_seq_   = seq_ret->get_seq_id ();
    return ret;
  }
  return syn::IEvent::ptr ();
}


syn::IEvent::ptr
RootModule::sync_msg_catch_func (
  syn::IEvent::ptr&           msg,
  bool                        forward,
  const StateProcessEventExt& process_state)
{
  if (forward)
  {
    current_seq_.sync_event_ = true;

    auto ret = ::libs::iproperties::helpers::cast_event< ::libs::events::ISyncEvent > (msg)->get_msg ();
    U3_ASSERT (ret);
    return ret;
  }

  if (::libs::iproperties::helpers::cast_event< ::libs::events::IAnswerEvent > (msg))
  {
    return msg;
  }
  return syn::IEvent::ptr ();
}


syn::IEvent::ptr
RootModule::request_msg_catch_func (
  syn::IEvent::ptr&           msg,
  bool                        forward,
  const StateProcessEventExt& process_state)
{
  if (forward)
  {
    current_seq_.request_ = true;
    auto ret              = ::libs::iproperties::helpers::cast_event< ::libs::events::IRequestEvent > (msg)->get_msg ();
    U3_ASSERT (ret);
    return ret;
  }
  //  инверсия, на запрос идет ответ.
  syn::IEvent::ptr rmsg;
  auto             dmsg = ::libs::iproperties::helpers::create_event< ::libs::events::IAnswerEvent > (rmsg);
  dmsg->set_msg (msg);
  return rmsg;
}


syn::IEvent::ptr
RootModule::answer_msg_catch_func (
  syn::IEvent::ptr&           msg,
  bool                        forward,
  const StateProcessEventExt& process_state)
{
  if (forward)
  {
    current_seq_.answer_ = true;
    auto ret             = ::libs::iproperties::helpers::cast_event< ::libs::events::IAnswerEvent > (msg)->get_msg ();
    U3_ASSERT (ret);
    return ret;
  }
  //  инверсия, пришел ответ модулю
  return msg;
}
}   // namespace libs::ilink::appl::root
