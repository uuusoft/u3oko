/**
\file       bufs-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "bufs-event.hpp"

namespace libs::ievents::runtime::mem
{
BufsEvent::BufsEvent (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
  events_        = nullptr;
}


BufsEvent::BufsEvent (
  const Acessor&,
  ::libs::bufs::Bufs::ptr&  buf,
  std::list< IEvent::ptr >* events) :
  buf_ (buf),
  events_ (events)
{
  property_name_ = gen_get_mid ();
}


BufsEvent::~BufsEvent ()
{
}


::libs::bufs::Bufs::ptr&
BufsEvent::get_buf ()
{
  return buf_;
}


void
BufsEvent::set_buf (::libs::bufs::Bufs::ptr& buf)
{
  buf_ = buf;
}


void
BufsEvent::set_events (events_type* events)
{
  events_ = events;
}


BufsEvent::events_type*
BufsEvent::get_events ()
{
  return events_;
}


::libs::events::IEvent::ptr
BufsEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< BufsEvent > (this, deep);
}


void
BufsEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (BufsEvent);
  super::copy_int (src);
  U3_ASSERT_SIGNAL ("unimplemented");
}

#if 0
template< class Archive >
void
BufsEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (buf_);

  self_correct ();
}
#endif
}   // namespace libs::ievents::runtime::mem

// BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::runtime::mem::BufsEvent );
// U3_BOOST_SERIALIZE_ALL_ARCHIVES( ::libs::ievents::runtime::mem::BufsEvent );
