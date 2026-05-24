/**
\file       read-data.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.07.2018
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "read-data.hpp"

namespace libs::istorage_events::events
{
ReadData::ReadData (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


ReadData::~ReadData ()
{
}


void
ReadData::set_stream_id (const stream_id_type& id)
{
  stream_id_ = id;
}


const stream_id_type&
ReadData::get_stream_id () const
{
  return stream_id_;
}


void
ReadData::set_msg (::libs::events::IEvent::ptr& buf)
{
  buf_ = buf;
}


::libs::events::IEvent::ptr
ReadData::get_msg () const
{
  return buf_;
}


::libs::events::IEvent::ptr
ReadData::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ReadData > (this, deep);
}


void
ReadData::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (ReadData);
  super::copy_int (src);
  stream_id_ = dsrc->stream_id_;
  buf_       = dsrc->buf_;
}


template< class Archive >
void
ReadData::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoistorage_eventsoeventsoBaseStorageEvent", super);
  ar& BOOST_SERIALIZATION_NVP (stream_id_);
  ar& BOOST_SERIALIZATION_NVP (buf_);

  self_correct ();
}
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::ReadData);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::istorage_events::events::ReadData);
