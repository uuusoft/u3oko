/**
\file       data-module-basemodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_module_data
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-mdata-includes_int.hpp"
#include "data-module.hpp"

namespace modules::uuu_mdata::appl
{
void
DataModule::appl_init_int (const ::libs::link::appl::InitApplication& info)
{
  super::appl_init_int (info);
  U3_CHECK (check_process (), "check_process");
  icore_ = ::libs::icore::create ();
}


void
DataModule::init_done_int ()
{
  if (!devices_)
  {
    // один раз получаем все устройства в системе, т.к. для некоторых типов (v4l2 for example) устройства можно проверить только в экслюзивном доступе
    // а после создания графов обработки данных (после вызова DataModule::init_done_int) мы его получить не сможем
    devices_   = all2events_->impl ()->get (syn::ListDevicesDataEvent::gen_get_mid ());
    auto props = ::libs::iproperties::helpers::cast_event< syn::ListDevicesDataEvent > (devices_);
    U3_ASSERT (props);
    process_list_devices (props, devices_);
    // debug
    auto        props1   = ::libs::iproperties::helpers::cast_event< syn::ListDevicesDataEvent > (devices_.get ());
    const auto& devices1 = props1->get_source_dll_names ();
    U3_LOG_DATA_MARK ("count sources" + VTOLOG (devices1.size ()));
    for (const auto& device1 : devices1)
    {
      U3_LOG_DATA_MARK ("found source" + TOLOG (device1));
    }
  }

  auto files = get_list_xml_files ();
  for (auto& folder : files.folders_)
  {
    try
    {
      const auto data_graph_state = get_data_graph_state (folder.name_);
      if (data_graph_state != ::libs::core::graph::GraphStates::disable)
      {
        U3_LOG_DATA_INFO ("create graph" + TOLOG (folder.name_));
        make_data_graph (folder.name_);
        update_cpu_graph (folder.name_);
        update_events_graph (folder.name_);
        start_graph (folder.name_);
      }
    }
    catch (const std::exception& e)
    {
      U3_LOG_DATA_EXCEPT (e.what ());
    }
  }
}


void
DataModule::init_proxys_int ()
{
  super::init_proxys_int ();
}


void
DataModule::init_links_int (const ::libs::link::appl::InitApplication& info)
{
  auto type_run = ::libs::link::details::CodeRuns::appl;
  auto lproxy   = ::libs::ilink::LinkCreatorProxy::instance ();

  auto temp_link = lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      type_run,
      std::string (""),
      "mpl_uuu_mdata",
      info.company_name_,
      info.appl_name_,
      "subsys_data",
      ::libs::link::details::ModuleLinks::mdata,
      ::libs::link::consts::size::buf_appl2data));

  links_.set (libs::properties::vers::links::mids::mdata2appl, temp_link);

  //  нужно установить свои связи в свойства разделяемые и спользовать их.
  {
    auto links = U3_CAST_PROP (syn::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    links->update_links_lockfree ().set (libs::properties::vers::links::mids::mdata2appl, links_.get (libs::properties::vers::links::mids::mdata2appl));
  }

  {
    logger_ = U3_CAST_PROP (syn::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().get (libs::properties::vers::links::mids::mdata2appl).lock ();

    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangDShowRunsSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::ilog_events::AppllPartLogInfo (
        ::libs::ievents::props::modules::log::LogLevels::info,
        ::modules::uuu_mdata::appl::consts::module_name,
        ::libs::helpers::log::get_module_version ()),
      "");

    props->set_start (true);
    links_.get (libs::properties::vers::links::mids::mdata2appl)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }
}


void
DataModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[::libs::ievents::runtime::video::FrameDone::gen_get_mid ()] =
    [] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::InfoCPUEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto props = ::libs::iproperties::helpers::cast_event< syn::InfoCPUEvent > (msg);
      process_info_cpu (props);
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::ChangeGraphsDataEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto props = ::libs::iproperties::helpers::cast_event< syn::ChangeGraphsDataEvent > (msg);
      U3_ASSERT (props);
      process_change_graphs_data (props);
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::ListDevicesDataEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      U3_ASSERT (devices_);
      U3_ASSERT (all2events_);
      auto srcprops        = ::libs::iproperties::helpers::cast_event< syn::ListDevicesDataEvent > (devices_);
      auto props           = ::libs::iproperties::helpers::cast_event< syn::ListDevicesDataEvent > (msg);
      auto srcdllnamestemp = srcprops->get_source_dll_names ();
      props->set_source_dll_names (std::move (srcdllnamestemp));
      for (std::size_t i = 0; i < props->get_source_dll_names ().size (); ++i)
      {
        auto devicesdlltemp = srcprops->get_devices_for_dll (i);
        props->set_devices_for_dll (i, std::move (devicesdlltemp));
      }
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::ListXmlFilesDataEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto props = ::libs::iproperties::helpers::cast_event< syn::ListXmlFilesDataEvent > (msg);
      U3_ASSERT (props);
      process_list_xml_files (props);
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::GetNodesDataEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto props = ::libs::iproperties::helpers::cast_event< syn::GetNodesDataEvent > (msg);
      U3_ASSERT (props);
      process_get_nodes (props);
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::ChangeNodeDataEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto props = ::libs::iproperties::helpers::cast_event< syn::ChangeNodeDataEvent > (msg);
      U3_ASSERT (props);
      process_change_node (props, msg);
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::ExpandTimesEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto props = ::libs::iproperties::helpers::cast_event< syn::ExpandTimesEvent > (msg);
      U3_ASSERT (props);
      process_expand_times (props, msg);
      return syn::IEvent::ptr ();
    }
    return msg;
  };
}


bool
DataModule::appl_deinit_int ()
{
  U3_XLOG_MARK ("DataModule::deinit_int begin")
  if (links_.get (libs::properties::vers::links::mids::mdata2appl))
  {
    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangDShowRunsSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::ilog_events::AppllPartLogInfo (
        ::libs::ievents::props::modules::log::LogLevels::info,
        ::modules::uuu_mdata::appl::consts::module_name,
        ::libs::helpers::log::get_module_version ()),
      "");

    props->set_start (false);
    links_.get (libs::properties::vers::links::mids::mdata2appl)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }

  for (auto& val : idatas_)
  {
    ptr_graph_type& graph = val.second;
    if (graph.expired ())
    {
      continue;
    }

    stop_graph (val.first);
    U3_CHECK_NT (icore_->delete_graph (graph), "DataModule::deinit_int");
    graph.reset ();
  }

  icore_.reset ();

  {
    auto links = U3_CAST_PROP (syn::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    links->update_links_lockfree ().reset_link (libs::properties::vers::links::mids::mdata2appl);
  }

  links_.get (libs::properties::vers::links::mids::mdata2appl)->destroy ();
  links_.reset_link (libs::properties::vers::links::mids::mdata2appl);
  return true;
}
}   // namespace modules::uuu_mdata::appl
