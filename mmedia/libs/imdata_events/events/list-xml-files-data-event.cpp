/**
\file       list-xml-files-data-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "list-xml-files-data-event.hpp"

namespace libs::imdata_events::events
{
DataGraphFolderInfoType::DataGraphFolderInfoType (
  const std::string&                      name,
  const ::libs::core::graph::GraphStates& graph_state) :
  folder_name_ (name),
  graph_state_ (graph_state)
{
}


DataGraphFolderInfoType::~DataGraphFolderInfoType ()
{
}


template< class Archive >
void
DataGraphFolderInfoType::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (folder_name_);
  ar& BOOST_SERIALIZATION_NVP (graph_state_);
}


ListXmlFilesDataEvent::ListXmlFilesDataEvent (const Acessor& ph, const data_graph_infos_types& data_graph_infos) :
  data_graph_states_ (data_graph_infos)
{
  property_name_ = gen_get_mid ();
}


ListXmlFilesDataEvent::~ListXmlFilesDataEvent ()
{
}


const ListXmlFilesDataEvent::data_graph_infos_types&
ListXmlFilesDataEvent::get_data_graph_states () const
{
  return data_graph_states_;
}


void
ListXmlFilesDataEvent::set_data_graph_states (data_graph_infos_types&& src)
{
  std::swap (data_graph_states_, src);
}


::libs::events::IEvent::ptr
ListXmlFilesDataEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ListXmlFilesDataEvent > (this, deep);
}


void
ListXmlFilesDataEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "ListXmlFilesDataEvent::load_json_int::not support");
}


void
ListXmlFilesDataEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  auto& values = obj["data_graph_states"].emplace_array ();
  for (const auto& data_graph_states : data_graph_states_)
  {
    values.push_back (
      ::boost::json::value {
        { "folder_name", data_graph_states.folder_name_ },
        { "graph_state", U3_CAST_UINT32_FORCE (data_graph_states.graph_state_) } });
  }
}


void
ListXmlFilesDataEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (ListXmlFilesDataEvent);
  super::copy_int (src);
  data_graph_states_ = dsrc->data_graph_states_;
}


template< class Archive >
void
ListXmlFilesDataEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoimdata_eventsoeventsoBaseDataEvent", super);
  ar& BOOST_SERIALIZATION_NVP (data_graph_states_);

  self_correct ();
}
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::DataGraphFolderInfoType);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::imdata_events::events::DataGraphFolderInfoType);

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::ListXmlFilesDataEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::imdata_events::events::ListXmlFilesDataEvent);
