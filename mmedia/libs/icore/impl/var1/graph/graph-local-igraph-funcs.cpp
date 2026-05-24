/**
\file       graph-local-igraph-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_icore_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../libs-icore-includes_int.hpp"
#include "../libs-icore-impl-var1-includes.hpp"
#include "mmedia/libs/helpers/thread/generic-thread-func.hpp"
#include "graph.hpp"

namespace libs::icore::impl::var1::graph
{
::libs::iproperties::appl_paths::Paths
get_type_path_by_name_file (const std::string& file_name)
{
  const auto len0 = strlen (::libs::core::consts::folders::internal_zero_funcs);
  if (file_name.length () >= len0 && file_name.substr (0, len0) == std::string (::libs::core::consts::folders::internal_zero_funcs))
  {
    return ::libs::iproperties::appl_paths::Paths::templates_data_module;
  }
  return ::libs::iproperties::appl_paths::Paths::active_data_module;
}


void
Graph::load_int (const std::string& folder)
{
  U3_ASSERT (!folder.empty ());

  ::libs::helpers::utils::TransformValueHelper< live_ext_requests_type > thelper (
    live_ext_requests_, [] (live_ext_requests_type& val) { ++val; }, [] (live_ext_requests_type& val) { --val; });

  lock_type                                lock (ctrl_graph_mtx_);
  auto                                     iappl = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();
  ::libs::iproperties::xml::InitLoaderInfo helper_info (iappl);
  ::libs::iproperties::xml::Loader         helper_xml (helper_info);

  data_graph_folder_ = folder;

  auto               type_path = get_type_path_by_name_file (folder);
  pugi::xml_document xml_path;
  xml_path.reset ();
  if (::libs::iproperties::xml::helpers::load_xml (&helper_xml, folder, type_path, xml_path))
  {
    ::pugi::xml_object_range< ::pugi::xml_named_node_iterator > range_nodes = xml_path.root ().children ("path");
    load_impl (range_nodes.begin ());
  }
}


const Graph::obj_ids_type&
Graph::get_objs_int ()
{
  ::libs::helpers::utils::TransformValueHelper< live_ext_requests_type > thelper (
    live_ext_requests_, [] (live_ext_requests_type& val) { ++val; }, [] (live_ext_requests_type& val) { --val; });

  lock_type lock (ctrl_graph_mtx_);
  return data_graph_obj_ids_;
}


void
Graph::send_event2obj_int (const syn::NodeID& id_obj, events::IEvent::ptr& evnt)
{
  U3_ASSERT (evnt);

  ::libs::helpers::utils::TransformValueHelper< live_ext_requests_type > thelper (
    live_ext_requests_, [] (live_ext_requests_type& val) { ++val; }, [] (live_ext_requests_type& val) { --val; });

  lock_type lock (ctrl_graph_mtx_);

  recive_special_event_impl (evnt);

  if (!id_obj.check ())
  {
    // такое бывает, когда используется сообщение для всего потока обработки данных. Надо бы скорректировать.
    U3_LOG_DATA_DBG ("check failed => skip send");
    return;
  }

  auto find_obj = id2data_graph_objs_.find (id_obj);
  if (id2data_graph_objs_.end () == find_obj)
  {
    U3_LOG_DATA_ERROR ("find obj graph by id " + id_obj.get_name () + TOLOG (data_graph_folder_));
    return;
  }

  find_obj->second->send_event2me (evnt);
}


void
Graph::set_logger_int (::libs::link::ILink::weak_ptr ptr)
{
  logger_ = ptr;
}
}   // namespace libs::icore::impl::var1::graph
