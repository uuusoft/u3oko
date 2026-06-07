/**
\file       BaseNodesDataEvent.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-nodes-data-event.hpp"

namespace libs::imdata_events::events
{
BaseNodesDataEvent::BaseNodesDataEvent (const Acessor& pha, const id_graph_type& id_graph) :
  id_graph_ (id_graph)
{
  property_name_ = gen_get_mid ();
}


const BaseNodesDataEvent::id_graph_type&
BaseNodesDataEvent::get_id_graph () const
{
  return id_graph_;
}


void
BaseNodesDataEvent::set_id_graph (id_graph_type&& id)
{
  std::swap (id_graph_, id);
}


bool
BaseNodesDataEvent::check () const
{
  U3_ASSERT (!id_graph_.empty ());
  return id_graph_.empty () ? false : true;
}


::libs::events::IEvent::ptr
BaseNodesDataEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< BaseNodesDataEvent > (this, deep);
}


void
BaseNodesDataEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  id_graph_ = ::libs::helpers::json::get_string (obj.at ("id_graph").as_string ());
}


void
BaseNodesDataEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  const auto temp = ::libs::helpers::json::to_string (id_graph_);
  obj["id_graph"] = temp;
}


void
BaseNodesDataEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseNodesDataEvent > (src);
  super::copy_int (src);
  id_graph_ = dsrc->id_graph_;
}


template< class Archive >
void
BaseNodesDataEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoimdata_eventsoeventsoBaseDataEvent", super);
  arh& BOOST_SERIALIZATION_NVP (id_graph_);

  self_correct ();
}
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::BaseNodesDataEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::imdata_events::events::BaseNodesDataEvent);
