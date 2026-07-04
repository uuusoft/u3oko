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
  id_name_type  name,
  dll_name_type name_dll) :
  id_node_name_ (std::move (name)),
  id_node_name_dll_ (std::move (name_dll))
{
}


auto
NodeID::get_name () const -> const NodeID::id_name_type
{
  return id_node_name_;
}


auto
NodeID::update_name () -> NodeID::id_name_type&
{
  return id_node_name_;
}


auto
NodeID::get_name_dll () const -> const NodeID::dll_name_type&
{
  return id_node_name_dll_;
}


auto
NodeID::update_name_dll () -> NodeID::dll_name_type&
{
  return id_node_name_dll_;
}


auto
NodeID::operator< (const NodeID& obj) const -> bool
{
  U3_ASSERT (check ());
  U3_ASSERT (obj.check ());
  return id_node_name_ < obj.id_node_name_;
}


auto
NodeID::operator== (const NodeID& obj) const -> bool
{
  U3_ASSERT (check ());
  U3_ASSERT (obj.check ());
  return id_node_name_ == obj.id_node_name_;
}


auto
NodeID::check () const -> bool
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


auto
get_ext_graph_node_id (const NodeID& id) -> std::string
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


auto
tag_invoke (::boost::json::value_to_tag< NodeID >, const ::boost::json::value& jvs) -> NodeID
{
  NodeID      ret;
  const auto& obj = jvs.as_object ();

  ::libs::utility::json::extract (obj, ret.update_name (), "id_node_name");
  ::libs::utility::json::extract (obj, ret.update_name_dll (), "id_node_name_dll");
  return ret;
}
}   // namespace libs::core::graph

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::core::graph::NodeID);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::core::graph::NodeID);
