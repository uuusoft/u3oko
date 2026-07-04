/**
\file       list-xml-files-data-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_media
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "list-xml-files-data-event.hpp"

namespace libs::events_media::events
{
DataGraphFolderInfoType::DataGraphFolderInfoType (
  std::string                             name,
  const ::libs::core::graph::GraphStates& graph_state) :
  folder_name_ (std::move (name)),
  graph_state_ (graph_state)
{
}


template< class Archive >
void
DataGraphFolderInfoType::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (folder_name_);
  arh& BOOST_SERIALIZATION_NVP (graph_state_);
}


ListXmlFilesDataEvent::ListXmlFilesDataEvent (const Acessor& pha, data_graph_infos_types data_graph_infos) :
  data_graph_states_ (std::move (data_graph_infos))
{
}


auto
ListXmlFilesDataEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ListXmlFilesDataEvent::gen_get_mid ();
}


auto
ListXmlFilesDataEvent::get_data_graph_states () const -> const ListXmlFilesDataEvent::data_graph_infos_types&
{
  return data_graph_states_;
}


void
ListXmlFilesDataEvent::set_data_graph_states (data_graph_infos_types&& src)
{
  std::swap (data_graph_states_, src);
}


auto
ListXmlFilesDataEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
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
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ListXmlFilesDataEvent > (src);
  super::copy_int (src);
  data_graph_states_ = dsrc->data_graph_states_;
}


template< class Archive >
void
ListXmlFilesDataEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_mediaoeventsoBaseDataEvent", super);
  arh& BOOST_SERIALIZATION_NVP (data_graph_states_);

  self_correct ();
}
}   // namespace libs::events_media::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_media::events::DataGraphFolderInfoType);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_media::events::DataGraphFolderInfoType);

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_media::events::ListXmlFilesDataEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_media::events::ListXmlFilesDataEvent);
