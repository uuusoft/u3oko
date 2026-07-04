/**
\file       bufs-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "bufs-event.hpp"

namespace libs::events_base::runtime::mem
{
BufsEvent::BufsEvent (const Acessor& pha)
{
}


BufsEvent::BufsEvent (
  const Acessor&,
  ::libs::bufs::Bufs::ptr&  buf,
  std::list< IEvent::ptr >* events) :
  buf_ (buf),
  events_ (events)
{
}


auto
BufsEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BufsEvent::gen_get_mid ();
}


auto
BufsEvent::get_buf () -> ::libs::bufs::Bufs::ptr&
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


auto
BufsEvent::get_events () -> BufsEvent::events_type*
{
  return events_;
}


auto
BufsEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< BufsEvent > (this, deep);
}


void
BufsEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BufsEvent > (src);
  super::copy_int (src);
  U3_ASSERT_SIGNAL ("unimplemented");
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
template< class Archive >
void
BufsEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP (super);
  arh& BOOST_SERIALIZATION_NVP (buf_);

  self_correct ();
}
#endif
}   // namespace libs::events_base::runtime::mem

// BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::events_base::runtime::mem::BufsEvent );
// U3_BOOST_ADD_SERIALIZE_ARCH( ::libs::events_base::runtime::mem::BufsEvent );
