/**
\file       type-object-id.cpp
\author     Erashov Anton erashov2026@proton.me
\date       24.06.2022
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "events-storage-includes_int.hpp"
#include "type-object-id.hpp"

namespace libs::events_storage
{
TypeObjectId::TypeObjectId (const id_type& val)
{
}


auto
TypeObjectId::is_valid () const -> bool
{
  return consts::empty_object_id == val_ ? false : true;
}


void
TypeObjectId::reset ()
{
  val_ = consts::empty_object_id;
}


auto
TypeObjectId::operator== (const TypeObjectId& obj) const -> bool
{
  return val_ == obj.val_;
}


template< class Archive >
void
TypeObjectId::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (val_);
}
}   // namespace libs::events_storage

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_storage::TypeObjectId);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_storage::TypeObjectId);
