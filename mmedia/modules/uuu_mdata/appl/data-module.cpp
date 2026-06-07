/**
\file       data-module.cpp
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
DataModule::DataModule ()
{
  try
  {
    auto iappl = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();

    text_id_module_  = ::libs::ilink::consts::id_data;
    resource_loader_ = std::make_shared< syn::Loader > (syn::InitLoaderInfo (iappl, true));
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
}


bool
DataModule::check_process ()
{
  sys_info_ = ::libs::helpers::sys::get_impl ();
  return true;
}


void
DataModule::process_info_cpu (syn::InfoCPUEvent::raw_ptr props)
{
  try
  {
    appl_event_props_.info_cpu_->copy (props);

    auto threads = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
    threads->set_count_threads (::libs::optim::mcalls::get_count_work_threads_by_count_cpu (props->get_cpu_count ()));

    std::for_each (
      idatas_.begin (),
      idatas_.end (),
      [this] (graphs_type::value_type& val) -> void {
        update_cpu_graph (val.first);
        return;
      });
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
}


void
DataModule::process_change_graphs_data (syn::ChangeGraphsDataEvent::raw_ptr props)
{
  try
  {
    const auto& action = props->get_action ();

    switch (action)
    {
    case syn::GraphActions::get: {
      syn::ChangeGraphsDataEvent::id_graphs_storage_type folders;

      for (const auto& val : idatas_)
      {
        folders.push_back (val.first);
      }
      props->set_graph_folders (folders);
      break;
    }
    case syn::GraphActions::add: {
      for (const auto& folder : props->get_graph_folders ())
      {
        U3_LOG_DATA_INFO ("change data graph {" + to_string (action) + "}:" + TOLOG (folder));
        try
        {
          prepare_graph (folder);
          make_data_graph (folder);
          update_cpu_graph (folder);
          update_events_graph (folder);
          start_graph (folder);
        }
        catch (const std::exception& e)
        {
          U3_LOG_DATA_EXCEPT (e.what ());
        }
      }
      break;
    }
    case syn::GraphActions::remove: {
      for (const auto& folder : props->get_graph_folders ())
      {
        U3_LOG_DATA_INFO ("change data graph {" + to_string (action) + "}:" + TOLOG (folder));
        delete_graph (folder, true);
      }
      break;
    }
    case syn::GraphActions::disable: {
      for (const auto& folder : props->get_graph_folders ())
      {
        U3_LOG_DATA_INFO ("change data graph {" + to_string (action) + "}:" + TOLOG (folder));
        set_data_graph_state (folder, ::libs::core::graph::GraphStates::disable);
        auto active_graph = get_graph (folder);
        if (!active_graph.expired ())
        {
          stop_graph (folder);
          delete_graph (folder);
        }
      }
      break;
    }
    case syn::GraphActions::enable: {
      for (const auto& folder : props->get_graph_folders ())
      {
        U3_LOG_DATA_INFO ("change data graph {" + to_string (action) + "}:" + TOLOG (folder));
        set_data_graph_state (folder, ::libs::core::graph::GraphStates::enable);
        auto active_graph = get_graph (folder);
        if (active_graph.expired ())
        {
          prepare_graph (folder);
          make_data_graph (folder);
          update_cpu_graph (folder);
          update_events_graph (folder);
          start_graph (folder);
        }
      }
      break;
    }
    default:
      U3_LOG_DATA_ERROR ("unknown type GraphActions: " + to_string (action));
      break;
    }
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
}


void
DataModule::process_list_xml_files (syn::ListXmlFilesDataEvent::raw_ptr props)
{
  try
  {
    auto                                               files = get_list_xml_files ();
    syn::ListXmlFilesDataEvent::data_graph_infos_types files2event;

    for (auto fit = files.folders_.begin (); fit != files.folders_.end (); ++fit)
    {
      files2event.emplace_back (
        fit->name_,
        get_data_graph_state (fit->name_));
    }

    props->set_data_graph_states (std::move (files2event));
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
}


void
DataModule::process_list_devices (
  syn::ListDevicesDataEvent::raw_ptr props,
  syn::IEvent::ptr&                  msg)
{
  try
  {
    //~EAI-TEST-02.03.2026
    const auto folder = std::string (::libs::core::consts::folders::internal_zero_funcs);
    auto       finger = idatas_.find (folder);

    if (idatas_.end () == finger)
    {
      U3_LOG_DATA_MARK ("create internal graph from" + TOLOG (folder));
      make_data_graph (folder);
      finger = idatas_.find (folder);
    }

    U3_CHECK (idatas_.end () != finger, "find data graph" + TOLOG (folder));
    auto graph = finger->second.lock ();
    if (!graph)
    {
      U3_LOG_DATA_ERROR ("create data graph" + TOLOG (folder));
      return;
    }

    graph->send_event2obj (syn::NodeID ("source"), msg);
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
}


void
DataModule::process_get_nodes (syn::GetNodesDataEvent::raw_ptr props)
{
  try
  {
    const auto& id_graph = props->get_id_graph ();
    auto        find_it  = idatas_.find (id_graph);

    if (find_it == idatas_.end ())
    {
      return;
    }

    if (auto find_graph = find_it->second.lock ())
    {
      const auto                              objs = find_graph->get_objs ();
      syn::GetNodesDataEvent::nodes_list_type nodes;

      for (const auto& obj : objs)
      {
        nodes.push_back (syn::GetNodesDataEvent::node_type (obj.get_name (), obj.get_name_dll ()));
      }
      props->set_nodes (nodes);
    }
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
}


void
DataModule::process_change_node (
  syn::ChangeNodeDataEvent::raw_ptr props,
  syn::IEvent::ptr&                 msg)
{
  try
  {
    const auto& id_graph = props->get_id_graph ();
    auto        find_it  = idatas_.find (id_graph);

    if (find_it == idatas_.end ())
    {
      U3_LOG_DATA_ERROR ("graph not found by id" + TOLOG (id_graph));
      return;
    }

    auto find_graph = find_it->second.lock ();
    if (!find_graph)
    {
      U3_LOG_DATA_ERROR ("try use empty graph id" + TOLOG (id_graph));
      return;
    }

    auto objs   = find_graph->get_objs ();
    auto id_obj = props->get_node ();

    find_graph->send_event2obj (id_obj, msg);

    if (::libs::imdata_events::events::GraphNodeActions::set == props->get_action ())
    {
      auto iappl = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();
      // for (auto& imsg : props->get_events ())
      {
        // const auto id_event         = props->get_events ().begin () != props->get_events ().end () ? props->get_events ().begin ()->get ()->get_mid () : msg->get_mid ();
        // const auto id_event         = imsg->get_mid ();
        const auto id_event         = msg->get_mid ();
        const auto saved_event_file = helpers::make_file_name_for_save_event (props->get_node ().get_name (), id_event);
        const auto saved_event_path = iappl->get_path (::libs::iproperties::appl_paths::Paths::active_data_module) + "/" + find_it->first + "/" + saved_event_file + "." + std::string (consts::event_file_extension);
        U3_LOG_DATA_INFO ("save event" + TOLOG (saved_event_file));

#if 1
        // json
        std::ofstream ofs (saved_event_path, std::ios_base::binary);
        ofs << msg->save_json ();
#elif 1
        // bin
        std::ofstream ofs (saved_event_path, std::ios_base::binary);
        ::libs::iproperties::helpers::event2bin (msg, ofs);
#else
        // xml
        std::string content;
        ::libs::iproperties::helpers::event2xml (msg, content);
        std::ofstream ofs (saved_event_path, std::ios_base::binary);
        ofs << content;
#endif
      }
    }
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
}


void
DataModule::process_expand_times (
  syn::ExpandTimesEvent::raw_ptr props,
  syn::IEvent::ptr&              msg)
{
  try
  {
    for (auto& idata : idatas_)
    {
      auto find_graph = idata.second.lock ();
      if (!find_graph)
      {
        U3_LOG_DATA_ERROR ("try use empty graph");
        return;
      }

      find_graph->send_event2obj (syn::NodeID (), msg);
    }

    U3_XLOG_DEV ("DataModule::process_expand_times");
#ifdef U3_FAKE_DISABLE
    if (::libs::ievents::runtime::state::Actions::get == props->get_action ())
    {
      // const auto info = props->get_stat ();
    }
    props->const storages_type& get_stat (const key_storage_type& key) const;
    void                        set_stat (const key_storage_type& key, const storages_type& infos);
    const Actions&              get_action () const;
    void                        set_action (const Actions& source);
#endif
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
}


DataModule::ptr_graph_type
DataModule::get_graph (const id_graph_type& graph_id)
{
  U3_ASSERT (!graph_id.empty ());
  auto val = idatas_.find (graph_id);
  if (val != idatas_.end ())
  {
    return val->second;
  }
  return DataModule::ptr_graph_type ();
}


void
DataModule::send_msg2graph (
  const id_graph_type&             graph_id,
  const syn::NodeID::name_id_type& sel_obj_id,
  syn::IEvent::ptr&                msg)
{
  auto wdata = get_graph (graph_id);
  auto graph = wdata.lock ();

  if (!graph)
  {
    U3_LOG_DATA_ERROR ("try use empty data graph" + TOLOG (graph_id));
    return;
  }

  const auto id_objs = graph->get_objs ();
  if (sel_obj_id.empty ())
  {
    for (const auto& id_obj : id_objs)
    {
      graph->send_event2obj (id_obj, msg);
    }
  }
  else
  {
    auto finger = id_objs.find (syn::NodeID (sel_obj_id, "skip dll name"));
    if (id_objs.end () != finger)
    {
      graph->send_event2obj (*finger, msg);
    }
  }
}


void
DataModule::update_cpu_graph (const id_graph_type& graph_id)
{
  auto      idemons = ::libs::iproperties::helpers::cast_prop_demons ();
  lock_type lock (idemons->get_sync ());
  auto      ioptim = idemons->get_optim_lockfree ()->impl ();
  auto      wdata  = get_graph (graph_id);
  auto      graph  = wdata.lock ();

  if (!appl_event_props_.info_cpu_)
  {
    U3_LOG_DATA_WRN ("skip update_cpu_graph - empty event");
    return;
  }

  auto info_cpu = ::libs::iproperties::helpers::cast_event< syn::InfoCPUEvent > (appl_event_props_.info_cpu_);
  ioptim->sync_impl (::libs::optim::io::TInit { info_cpu->get_cpu_type () });

  if (graph)
  {
    send_msg2graph (graph_id, "", appl_event_props_.info_cpu_);
  }
}


void
DataModule::update_events_graph (const id_graph_type& graph_id)
{
  auto                                    idemons = ::libs::iproperties::helpers::cast_prop_demons ();
  lock_type                               lock (idemons->get_sync ());
  auto                                    wdata             = get_graph (graph_id);
  auto                                    graph             = wdata.lock ();
  auto                                    iappl             = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();
  const std::string                       graph_events_path = iappl->get_path (syn::Paths::active_data_module) + "/" + graph_id;
  const std::string                       mask              = "?." + std::string (consts::event_file_extension) + "?";
  ::libs::helpers::files::DefaultFileMask enum_cond (mask);
  syn::NodeEnumFiles                      enum_files;

  U3_LOG_DATA_INFO ("update events for:" + TOLOG (graph_id));

  ::libs::helpers::files::get_files (
    graph_events_path,
    enum_files,
    { ::libs::helpers::files::IncludeSubFolders::disabled,
      ::libs::helpers::files::IncludeFiles::enabled,
      ::libs::helpers::files::Recursives::disabled },
    enum_cond);

  for (const auto& file : enum_files.files_)
  {
    bool                      delete_event_file = false;
    const std::string         event_path        = graph_events_path + "/" + file.name_;
    syn::NodeID::name_id_type node_id;
    std::string               event_id;
    std::string               file_json;

    helpers::split_event_file_name2parts (file.name_, node_id, event_id);

    try
    {
      auto          msg = libs::iproperties::helpers::get_pure_event_int (event_id);
      std::ifstream ifs (event_path, std::ios::binary);

      if (ifs.is_open ())
      {
        ifs >> file_json;
        msg->load_json (file_json);
      }

      if (::libs::iproperties::helpers::cast_event< ::libs::ievents::runtime::RuntimeEvent > (msg))
      {
        // ::libs::ievents::runtime::RuntimeEvent свойства не пересылаем в граф, REFACT: нужно избавиться вообще от сохранения таких свойств
        continue;
      }

      send_msg2graph (graph_id, node_id, msg);
    }
    catch (const std::exception& e)
    {
      U3_LOG_DATA_EXCEPT (TOLOG (event_path) + e.what ());
      delete_event_file = true;
    }

    if (delete_event_file)
    {
      U3_LOG_DATA_WRN ("delete invalid event file" + TOLOG (event_path));
      U3_XLOG_DBG (TOLOG (file_json));
      U3_CHECK (std::filesystem::remove (event_path), "std::filesystem::remove" + TOLOG (event_path));
      try
      {
        U3_LOG_DATA_MARK ("create default event file" + TOLOG (event_path));
        auto          msg = libs::iproperties::helpers::get_pure_event_int (event_id);
        std::ofstream ofs (event_path, std::ios_base::binary);
        ofs << msg->save_json ();
      }
      catch (const std::exception& e)
      {
        U3_LOG_DATA_EXCEPT (TOLOG (event_path) + e.what ());
      }
    }
  }
}


void
DataModule::delete_graph (const id_graph_type& graph_id, bool permanent)
{
  auto wdata = get_graph (graph_id);
  if (wdata.expired ())
  {
    return;
  }

  U3_ASSERT (1 == wdata.use_count ());
  icore_->delete_graph (wdata);
  idatas_.erase (graph_id);

  if (permanent)
  {
    auto       iappl       = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();
    const auto path2folder = ::libs::helpers::files::make_path (iappl->get_path (syn::Paths::active_data_module), graph_id);
    U3_LOG_DATA_INFO ("permanent delete data path" + TOLOG (path2folder));
    ::libs::helpers::files::delete_folder (path2folder);
  }
}


bool
split_folder_for_find_template (
  const std::string& folder,
  std::string&       dll_name,
  std::string&       device,
  int&               device_number)
{
  auto split1 = folder.find ('+');
  auto split2 = folder.find ('+', split1 + 1);

  if (std::string::npos == split1 || std::string::npos == split2)
  {
    return false;
  }

  dll_name      = ::libs::helpers::dlls::undecorate_dll_name (folder.substr (0, split1));
  device        = folder.substr (split1 + 1, split2 - 1 - split1);
  device_number = std::stoi (folder.substr (split2 + 1));
  return true;
}


std::string
DataModule::find_template_for_graph (const std::string& folder) const
{
  syn::InitLoaderInfo helper_info (std::const_pointer_cast< const ::libs::iproperties::appl_paths::IAppPaths > (paths_));
  syn::Loader         helper (helper_info);
  std::string         dll_name;
  std::string         device;
  std::int32_t        device_number = 0;

  if (!split_folder_for_find_template (folder, dll_name, device, device_number))
  {
    U3_LOG_DATA_ERROR ("split_folder_for_find_template" + TOLOG (folder) + TOLOG (dll_name) + TOLOG (device));
    return "";
  }

  const std::string candidates[] = {
    folder,
    dll_name + "+" + device,
    dll_name,
    "default"
  };

  for (const auto& candidate : candidates)
  {
    if (helper.is_folder_exist (candidate, syn::Paths::templates_data_module))
    {
      return candidate;
    }
  }
  return {};
}


void
DataModule::update_template_for_graph (
  const std::string& path2folder,
  const std::string& folder) const
{
  std::string  dll_name;
  std::string  device;
  std::int32_t device_number = 0;

  if (!split_folder_for_find_template (folder, dll_name, device, device_number))
  {
    U3_LOG_DATA_ERROR ("split_folder_for_find_template" + TOLOG (folder) + TOLOG (dll_name) + TOLOG (device));
    return;
  }

  auto                                ucam_name = boost::uuids::random_generator () ();
  const ::libs::helpers::utils::cuuid cam_name (ucam_name);

  // Значения типа UUU_XML_ID должны совпадать со сначениями в шаблонах
  const ::libs::helpers::strings::syn::replace_val_type tmps2vals[] = {
    { "UUU_XML_ID__________VSD_GEN_VGEN__________VIDEO_DRIVER_PROP__________TYPE__________PLACEHOLDER", dll_name },
    { "UUU_XML_ID__________VSD_GEN_VGEN__________VIDEO_DRIVER_PROP__________NAME__________PLACEHOLDER", ::libs::helpers::json::to_string (device) },
    { "UUU_XML_ID__________VSD_GEN_VGEN__________VIDEO_DRIVER_PROP__________INDX_DEVICE__________PLACEHOLDER", std::to_string (device_number) },
    { "UUU_XML_ID__________VDD_BASE_ID__________BASE_ID_PROP__________SOURCE_NAME__________PLACEHOLDER", ::libs::helpers::utils::to_string (cam_name) }
  };

  ::libs::helpers::files::replace_strings_in_files (path2folder, tmps2vals, std::size (tmps2vals));
}


bool
DataModule::is_graph_folder_exist (const std::string& folder) const
{
  syn::InitLoaderInfo helper_info (std::const_pointer_cast< const ::libs::iproperties::appl_paths::IAppPaths > (paths_));
  syn::Loader         helper (helper_info);

  return helper.is_folder_exist (folder, syn::Paths::active_data_module);
}


void
DataModule::prepare_graph (const std::string& folder)
{
  if (is_graph_folder_exist (folder))
  {
    //  Если директория уже существует - значит устройство от источника уже добавлено
    U3_LOG_DATA_WRN ("folder allready exist" + TOLOG (folder));
    return;
  }

  const auto xmltemplate = find_template_for_graph (folder);
  if (xmltemplate.empty ())
  {
    U3_LOG_DATA_ERROR ("xmltemplate file not found" + TOLOG (folder));
    return;
  }

  syn::InitLoaderInfo helper_info (std::const_pointer_cast< const ::libs::iproperties::appl_paths::IAppPaths > (paths_));
  syn::Loader         helper (helper_info);
  const auto          active_data_graphs = paths_->get_path (syn::Paths::active_data_module);
  const std::string   temp               = ::libs::helpers::files::make_path (active_data_graphs, xmltemplate);
  const std::string   dest               = ::libs::helpers::files::make_path (active_data_graphs, folder);
  std::error_code     error;

  ::libs::iproperties::xml::helpers::copy_files (
    helper,
    syn::Paths::templates_data_module,
    xmltemplate,
    active_data_graphs);

  std::filesystem::rename (temp, dest, error);
  if (error)
  {
    U3_LOG_DATA_ERROR ("rename xmltemplate's folder for new path" + TOLOG (temp) + TOLOG (dest) + ": " + error.message ());
    std::filesystem::remove_all (dest, error);
    return;
  }

  update_template_for_graph (dest, folder);
}


void
DataModule::make_data_graph (const std::string& folder)
{
  U3_LOG_DATA_MARK (std::string ("make graph from" + TOLOG (folder)));
  // EAI-REFACT нужно блять ислючить исключения или обрабатывать их по месту
  // При загрузке пути допустимы исключения, связанные с ошибками в xml пути, которые не являются фатальными
  try
  {
    U3_CHECK (!folder.empty (), "try make data graph from empty xml file");
    delete_graph (folder);
    idatas_[folder] = icore_->create_graph ();
    auto graph      = idatas_[folder].lock ();
    U3_CHECK (graph, "return empty graph");
    graph->set_logger (logger_);
    graph->load (folder + "/" + std::string (consts::data_graph_xml_file_name));
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (TOLOG (folder) + " " + boost::diagnostic_information (e));
  }
}


void
DataModule::start_graph (const id_graph_type& graph_id)
{
  U3_LOG_DATA_INFO ("start graph" + TOLOG (graph_id));
  syn::IEvent::ptr rmsg;
  auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateProcessEvent > (rmsg);

  dmsg->set_start (true);
  send_msg2graph (graph_id, "", rmsg);
}


void
DataModule::stop_graph (const id_graph_type& graph_id)
{
  U3_LOG_DATA_INFO ("stop graph" + TOLOG (graph_id));
  syn::IEvent::ptr rmsg;
  auto             dmsg = ::libs::iproperties::helpers::create_event< syn::ChangeStateProcessEvent > (rmsg);

  dmsg->set_start (false);
  send_msg2graph (graph_id, "", rmsg);
}


syn::NodeEnumFiles
DataModule::get_list_xml_files ()
{
  auto                apppaths = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();
  syn::InitLoaderInfo loader_info (apppaths);
  syn::Loader         loader (loader_info);
  syn::NodeEnumFiles  files;

  loader.get_enum (syn::Paths::active_data_module, files, "");
  return files;
}


::libs::core::graph::GraphStates
DataModule::get_data_graph_state (const std::string& folder) const
{
  if (!is_graph_folder_exist (folder))
  {
    U3_LOG_DATA_WRN ("folder not exist" + TOLOG (folder));
    return ::libs::core::graph::GraphStates::unknown;
  }

  const auto    path2folder = ::libs::helpers::files::make_path (paths_->get_path (syn::Paths::active_data_module), folder);
  const auto    path2file   = ::libs::helpers::files::make_path (path2folder, std::string (consts::data_graph_state_file_name));
  std::ifstream reader (path2file);
  std::uint32_t temp_ret = graph_state_type_to_raw (libs::core::graph::GraphStates::enable);

  if (reader.is_open ())
  {
    reader >> temp_ret;
  }
  return ::libs::helpers::casts::static_cast_helper< ::libs::core::graph::GraphStates > (temp_ret);
}


void
DataModule::set_data_graph_state (
  const std::string&                      folder,
  const ::libs::core::graph::GraphStates& state)
{
  if (!is_graph_folder_exist (folder))
  {
    U3_LOG_DATA_WRN ("folder not exist" + TOLOG (folder));
    return;
  }

  const auto    path2folder = ::libs::helpers::files::make_path (paths_->get_path (syn::Paths::active_data_module), folder);
  const auto    path2file   = ::libs::helpers::files::make_path (path2folder, std::string (consts::data_graph_state_file_name));
  std::ofstream writer (path2file);

  if (!writer.is_open ())
  {
    U3_LOG_DATA_ERROR ("open file for writing state" + TOLOG (path2file));
    return;
  }

  writer << ::libs::helpers::casts::reinterpret_cast_helper< const std::uint32_t& > (state);
}
}   // namespace modules::uuu_mdata::appl
