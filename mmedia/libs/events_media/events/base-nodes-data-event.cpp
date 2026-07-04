/**
\file       BaseNodesDataEvent.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_media
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-nodes-data-event.hpp"

namespace libs::events_media::events
{
BaseNodesDataEvent::BaseNodesDataEvent (const Acessor& pha, id_graph_type id_graph) :
  id_graph_ (std::move (id_graph))
{
}


auto
BaseNodesDataEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BaseNodesDataEvent::gen_get_mid ();
}


auto
BaseNodesDataEvent::get_id_graph () const -> const BaseNodesDataEvent::id_graph_type&
{
  return id_graph_;
}


void
BaseNodesDataEvent::set_id_graph (id_graph_type&& id)
{
  std::swap (id_graph_, id);
}


auto
BaseNodesDataEvent::check () const -> bool
{
  U3_ASSERT (!id_graph_.empty ());
  return id_graph_.empty () ? false : true;
}


auto
BaseNodesDataEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< BaseNodesDataEvent > (this, deep);
}


void
BaseNodesDataEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  id_graph_ = ::libs::utility::json::get_string (obj.at ("id_graph").as_string ());
}


void
BaseNodesDataEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  const auto temp = ::libs::utility::json::to_string (id_graph_);
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
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_mediaoeventsoBaseDataEvent", super);
  arh& BOOST_SERIALIZATION_NVP (id_graph_);

  self_correct ();
}
}   // namespace libs::events_media::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_media::events::BaseNodesDataEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_media::events::BaseNodesDataEvent);
