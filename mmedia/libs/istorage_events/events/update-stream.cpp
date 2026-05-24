/**
\file       update-stream.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.07.2018
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "update-stream.hpp"

namespace libs::istorage_events::events
{
UpdateStream::UpdateStream (const Acessor& ph) :
  operation_ (StreamActions::read),
  direction_ (StreamDirections::unknown)
{
  property_name_ = gen_get_mid ();
}


UpdateStream::~UpdateStream ()
{
}


::libs::events::IEvent::ptr
UpdateStream::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< UpdateStream > (this, deep);
}


void
UpdateStream::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (UpdateStream);
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
UpdateStream::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoistorage_eventsoeventsoBaseStorageEvent", super);
  ar& BOOST_SERIALIZATION_NVP (obj_id_);
  ar& BOOST_SERIALIZATION_NVP (operation_);
  ar& BOOST_SERIALIZATION_NVP (stream_id_);
  ar& BOOST_SERIALIZATION_NVP (action_);
  ar& BOOST_SERIALIZATION_NVP (direction_);
  ar& BOOST_SERIALIZATION_NVP (time_);

  self_correct ();
}
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::UpdateStream);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::istorage_events::events::UpdateStream);
