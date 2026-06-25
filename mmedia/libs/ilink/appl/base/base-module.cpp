/**
\file       base-module.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_ilink
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "base-module.hpp"

namespace libs::ilink::appl::base
{
BaseModule::BaseModule ()
{
  register_events_for_module ();
}


void
register_events_for_module ()
{
  ::libs::events::register_events_in_archives ();
  ::libs::ievents::register_events_in_archives ();
  ::libs::ilog_events::events::register_events_in_archives ();
  ::libs::ievents_events::events::register_events_in_archives ();
  ::libs::igui_events::events::register_events_in_archives ();
  ::libs::imdata_events::events::register_events_in_archives ();
  ::libs::ihttp_events::events::register_events_in_archives ();
  ::libs::istorage_events::events::register_events_in_archives ();
}


void
update_template_for_application (const std::string& path2folder, const std::string& name)
{
  const auto                          bcid = boost::uuids::random_generator () ();
  const ::libs::helpers::utils::cuuid machine_cid (bcid);

  const ::libs::helpers::strings::syn::replace_val_type tmps2vals[] = {
    { "UUU_XML_ID__________MACHINE__________NAME__________ID__________PLACEHOLDER", ::libs::helpers::utils::to_string (machine_cid) },
    { "UUU_XML_ID__________MACHINE__________GUID__________ID__________PLACEHOLDER", ::boost::lexical_cast< std::string > (machine_cid.get_raw_uuid_vals ()) }
  };

  const auto counter_ops = ::libs::helpers::files::replace_strings_in_files (path2folder, tmps2vals, std::size (tmps2vals));
  U3_CHECK_NT (counter_ops > 0U, "failed, zero replace in templates" + VTOLOG (counter_ops) + TOLOG (path2folder));
}


void
BaseModule::load_events_props ()
{
  U3_XLOG_DBG ("BaseModule::load_events_props::---->" + TOLOG (text_id_module_));
  const std::string                        name ("sign-ready-init-appl.xml");
  ::libs::iproperties::xml::InitLoaderInfo helper_info (paths_);
  ::libs::iproperties::xml::Loader         helper_xml (helper_info);
  const auto                               active_paths = paths_->get_path (::libs::iproperties::appl_paths::Paths::active_appl_module);

  if (!helper_xml.is_file_exist (name, ::libs::iproperties::appl_paths::Paths::active_appl_module))
  {
    U3_XLOG_MARK ("file" + TOLOG (name) + " not found in" + TOLOG (active_paths) + " ---> create new application instance");
    // U3_XLOG_MARK ("prepare assets, copy file" + TOLOG (name) + " to folder" + TOLOG (active_paths));
    const auto templates_paths = paths_->get_path (libs::iproperties::appl_paths::Paths::templates_appl_module);
    U3_XLOG_MARK ("prepare assets, copy folder" + TOLOG (templates_paths) + " to folder" + TOLOG (active_paths));
    ::libs::iproperties::xml::helpers::copy_files (helper_xml, libs::iproperties::appl_paths::Paths::templates_appl_module, "", active_paths);
    U3_XLOG_MARK ("update templates for new application instance");
    update_template_for_application (active_paths, name);
  }

  try
  {
    ::libs::ilink::appl::helpers::load_event_from_json_file (active_paths, appl_event_props_.info_cpu_);
    ::libs::ilink::appl::helpers::load_event_from_json_file (active_paths, appl_event_props_.module_log_);
    ::libs::ilink::appl::helpers::load_event_from_json_file (active_paths, appl_event_props_.storage_module_);
  }
  catch (const std::exception& excpt)
  {
    U3_XLOG_ERROR (excpt.what ());
  }

  {
    auto* log_appl        = ::libs::iproperties::helpers::cast_event< syn::PropertyLogModuleEvent > (appl_event_props_.module_log_);
    syn::log::g_log_level = ::libs::ievents::props::modules::log::from_raw_val (log_appl->get_val (syn::LogVals::log_level));
  }
}


void
BaseModule::update_events_props ()
{
  U3_XLOG_DBG ("BaseModule::update_events_props::---->" + TOLOG (text_id_module_));
  auto*                           orinfo = ::libs::iproperties::helpers::get_shared_prop_os ();
  syn::ISharedProperty::lock_type lock (orinfo->get_sync ());
  if (orinfo->get_appl_lockfree ())
  {
    return;
  }

  U3_XLOG_DBG ("BaseModule::update_events_props:: real work" + TOLOG (text_id_module_));
  auto* main_appl = ::libs::iproperties::helpers::cast_event< syn::ApplicationProp > (appl_event_props_.main_appl_properties_);
  auto* log_appl  = ::libs::iproperties::helpers::cast_event< syn::PropertyLogModuleEvent > (appl_event_props_.module_log_);
  auto* info_cpu  = ::libs::iproperties::helpers::cast_event< syn::InfoCPUEvent > (appl_event_props_.info_cpu_);
  // auto* storage_appl = ::libs::iproperties::helpers::cast_event< ::libs::ievents::props::modules::storage::PropertyStorageModuleEvent > (appl_event_props_.storage_module_);

  orinfo->set_appl_lockfree (main_appl);
  orinfo->set_log_lockfree (log_appl);
  orinfo->set_paths_lockfree (paths_);

  if (::libs::helpers::sys::cpu::CpuExts::max == info_cpu->get_cpu_type ())
  {
    U3_XLOG_MARK ("update cpu extension" + VTOLOG (U3_CAST_INT32_FORCE (cpu_informer_.get_max ())));
    info_cpu->set_cpu_type (cpu_informer_.get_max ());
  }

  if (0 == info_cpu->get_cpu_count ())
  {
    info_cpu->set_cpu_count (sys_info_->count_cpu ());
  }

  {
    mthreads_ = std::make_shared< ::libs::optim::mcalls::CallerImpl > ();
    mthreads_->set_count_threads (::libs::optim::mcalls::get_count_work_threads_by_count_cpu (info_cpu->get_cpu_count ()));
    orinfo->set_mcalls_lockfree (mthreads_);
  }
}


auto
BaseModule::get_recv_link () -> recv_links_type
{
  auto ret = get_recv_link_int ();
  U3_CHECK_NT (!ret.empty (), "BaseModule::get_recv_link empty ret");
  return ret;
}
}   // namespace libs::ilink::appl::base
