/**
\file       update-stream.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "update-stream.hpp"

namespace libs::istorage_events::events
{
UpdateStream::UpdateStream (const Acessor& pha) :
  operation_ (StreamActions::read),
  direction_ (StreamDirections::unknown)
{
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
UpdateStream::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< UpdateStream > (this, deep);
}


void
UpdateStream::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< UpdateStream > (src);
  super::copy_int (src);

  obj_id_    = dsrc->obj_id_;
  stream_id_ = dsrc->stream_id_;
  action_    = dsrc->action_;
  direction_ = dsrc->direction_;
  time_      = dsrc->time_;
  operation_ = dsrc->operation_;
}


template< class Archive >
void
UpdateStream::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoistorage_eventsoeventsoBaseStorageEvent", super);
  arh& BOOST_SERIALIZATION_NVP (obj_id_);
  arh& BOOST_SERIALIZATION_NVP (operation_);
  arh& BOOST_SERIALIZATION_NVP (stream_id_);
  arh& BOOST_SERIALIZATION_NVP (action_);
  arh& BOOST_SERIALIZATION_NVP (direction_);
  arh& BOOST_SERIALIZATION_NVP (time_);

  self_correct ();
}
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::UpdateStream);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::istorage_events::events::UpdateStream);
