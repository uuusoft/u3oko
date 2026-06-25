/**
\file       node-graph-info.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_imdata_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "node-graph-info.hpp"

namespace libs::imdata_events::events
{
NodeGraphInfo::NodeGraphInfo (const std::string& id, const std::string& name_dll) :
  id_ (id),
  name_dll_ (name_dll)
{
}


bool
NodeGraphInfo::check () const
{
  return id_.empty () || name_dll_.empty () ? false : true;
}


std::string&
NodeGraphInfo::update_id ()
{
  return id_;
}


const std::string&
NodeGraphInfo::get_id () const
{
  return id_;
}


std::string&
NodeGraphInfo::update_name_dll ()
{
  return name_dll_;
}


const std::string&
NodeGraphInfo::get_name_dll () const
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


NodeGraphInfo
tag_invoke (::boost::json::value_to_tag< NodeGraphInfo >, const ::boost::json::value& jvs)
{
  NodeGraphInfo                ret;
  const ::boost::json::object& obj = jvs.as_object ();
  ::libs::helpers::json::extract (obj, ret.update_id (), "id");
  ::libs::helpers::json::extract (obj, ret.update_name_dll (), "name_dll");
  return ret;
}
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::NodeGraphInfo);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::imdata_events::events::NodeGraphInfo);
