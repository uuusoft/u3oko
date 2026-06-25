/**
\file       write-data.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "write-data.hpp"

namespace libs::istorage_events::events
{
WriteData::WriteData (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


void
WriteData::set_stream_id (const stream_id_type& id)
{
  stream_id_ = id;
}


const stream_id_type&
WriteData::get_stream_id () const
{
  return stream_id_;
}


void
WriteData::set_msg (::libs::events::IEvent::ptr& buf)
{
  buf_ = buf;
}


::libs::events::IEvent::ptr
WriteData::get_msg () const
{
  return buf_;
}


::libs::events::IEvent::ptr
WriteData::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< WriteData > (this, deep);
}


void
WriteData::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< WriteData > (src);
  super::copy_int (src);

  stream_id_ = dsrc->stream_id_;
  buf_       = dsrc->buf_;
}


template< class Archive >
void
WriteData::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoistorage_eventsoeventsoBaseStorageEvent", super);
  arh& BOOST_SERIALIZATION_NVP (stream_id_);
  arh& BOOST_SERIALIZATION_NVP (buf_);

  self_correct ();
}
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::WriteData);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::istorage_events::events::WriteData);
