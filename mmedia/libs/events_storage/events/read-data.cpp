/**
\file       read-data.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-storage-includes_int.hpp"
#include "read-data.hpp"

namespace libs::events_storage::events
{
ReadData::ReadData (const Acessor& pha)
{
}


auto
ReadData::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ReadData::gen_get_mid ();
}


void
ReadData::set_stream_id (const stream_id_type& id)
{
  stream_id_ = id;
}


auto
ReadData::get_stream_id () const -> const stream_id_type&
{
  return stream_id_;
}


void
ReadData::set_msg (::libs::events::IEvent::ptr& buf)
{
  buf_ = buf;
}


auto
ReadData::get_msg () const -> ::libs::events::IEvent::ptr
{
  return buf_;
}


auto
ReadData::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< ReadData > (this, deep);
}


void
ReadData::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ReadData > (src);
  super::copy_int (src);

  stream_id_ = dsrc->stream_id_;
  buf_       = dsrc->buf_;
}


template< class Archive >
void
ReadData::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_storageoeventsoBaseStorageEvent", super);
  arh& BOOST_SERIALIZATION_NVP (stream_id_);
  arh& BOOST_SERIALIZATION_NVP (buf_);

  self_correct ();
}
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_storage::events::ReadData);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_storage::events::ReadData);
