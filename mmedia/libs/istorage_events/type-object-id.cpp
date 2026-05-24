/**
\file       type-object-id.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.06.2022
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "istorage-events-includes_int.hpp"
#include "type-object-id.hpp"

namespace libs::istorage_events
{
TypeObjectId::TypeObjectId (const id_type& val)
{
}


TypeObjectId::~TypeObjectId ()
{
}


bool
TypeObjectId::is_valid () const
{
  return consts::empty_object_id == val_ ? false : true;
}


void
TypeObjectId::reset ()
{
  val_ = consts::empty_object_id;
}


bool
TypeObjectId::operator== (const TypeObjectId& obj) const
{
  return val_ == obj.val_;
}


template< class Archive >
void
TypeObjectId::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (val_);
}
}   // namespace libs::istorage_events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::TypeObjectId);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::istorage_events::TypeObjectId);
