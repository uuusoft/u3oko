/**
\file       node-id.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_core_lib
*/
#include "../libs-cores-core-includes_int.hpp"
#include "node-id.hpp"

namespace libs::core::graph
{
NodeID::NodeID (
  const name_id_type&  name,
  const name_dll_type& name_dll) :
  id_node_name_ (name),
  id_node_name_dll_ (name_dll)
{
}


const NodeID::name_id_type
NodeID::get_name () const
{
  return id_node_name_;
}


NodeID::name_id_type&
NodeID::update_name ()
{
  return id_node_name_;
}


const NodeID::name_dll_type&
NodeID::get_name_dll () const
{
  return id_node_name_dll_;
}


NodeID::name_dll_type&
NodeID::update_name_dll ()
{
  return id_node_name_dll_;
}


bool
NodeID::operator< (const NodeID& obj) const
{
  U3_ASSERT (check ());
  U3_ASSERT (obj.check ());
  return id_node_name_ < obj.id_node_name_;
}


bool
NodeID::operator== (const NodeID& obj) const
{
  U3_ASSERT (check ());
  U3_ASSERT (obj.check ());
  return id_node_name_ == obj.id_node_name_;
}


bool
NodeID::check () const
{
  return id_node_name_.empty () ? false : true;
}


template< class Archive >
void
NodeID::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (id_node_name_);
  arh& BOOST_SERIALIZATION_NVP (id_node_name_dll_);
}


std::string
get_ext_graph_node_id (const NodeID& id)
{
  return id.get_name () + "##" + id.get_name_dll ();
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const NodeID& src)
{
  jvs = {
    { "id_node_name", ::boost::json::value_from (src.get_name ()) },
    { "id_node_name_dll", ::boost::json::value_from (src.get_name_dll ()) }
  };
}


NodeID
tag_invoke (::boost::json::value_to_tag< NodeID >, const ::boost::json::value& jvs)
{
  NodeID      ret;
  const auto& obj = jvs.as_object ();

  ::libs::helpers::json::extract (obj, ret.update_name (), "id_node_name");
  ::libs::helpers::json::extract (obj, ret.update_name_dll (), "id_node_name_dll");
  return ret;
}
}   // namespace libs::core::graph

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::core::graph::NodeID);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::core::graph::NodeID);
