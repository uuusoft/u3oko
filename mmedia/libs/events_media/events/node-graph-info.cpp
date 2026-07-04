/**
\file       node-graph-info.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_media
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "node-graph-info.hpp"

namespace libs::events_media::events
{
NodeGraphInfo::NodeGraphInfo (std::string id, std::string name_dll) :
  id_ (std::move (id)),
  name_dll_ (std::move (name_dll))
{
}


auto
NodeGraphInfo::check () const -> bool
{
  return id_.empty () || name_dll_.empty () ? false : true;
}


auto
NodeGraphInfo::update_id () -> std::string&
{
  return id_;
}


auto
NodeGraphInfo::get_id () const -> const std::string&
{
  return id_;
}


auto
NodeGraphInfo::update_name_dll () -> std::string&
{
  return name_dll_;
}


auto
NodeGraphInfo::get_name_dll () const -> const std::string&
{
  return name_dll_;
}


template< class Archive >
void
NodeGraphInfo::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (id_);
  arh& BOOST_SERIALIZATION_NVP (name_dll_);
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const NodeGraphInfo& src)
{
  jvs = {
    { "id", src.get_id () },
    { "name_dll", src.get_name_dll () }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< NodeGraphInfo >, const ::boost::json::value& jvs) -> NodeGraphInfo
{
  NodeGraphInfo                ret;
  const ::boost::json::object& obj = jvs.as_object ();
  ::libs::utility::json::extract (obj, ret.update_id (), "id");
  ::libs::utility::json::extract (obj, ret.update_name_dll (), "name_dll");
  return ret;
}
}   // namespace libs::events_media::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_media::events::NodeGraphInfo);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_media::events::NodeGraphInfo);
