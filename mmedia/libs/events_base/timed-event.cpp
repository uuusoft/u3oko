/**
\file       timed-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "events-base-includes_int.hpp"
#include "timed-event.hpp"

namespace libs::events_base
{
TimedEvent::TimedEvent (const Acessor& pha) :
  time_ (boost::posix_time::microsec_clock::universal_time ())
{
}


auto
TimedEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return TimedEvent::gen_get_mid ();
}


auto
TimedEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< TimedEvent > (this, deep);
}


auto
TimedEvent::get_time () const -> const time_type&
{
  return time_;
}


void
TimedEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< TimedEvent > (src);
  super::copy_int (src);
  time_ = dsrc->time_;
}


template< class Archive >
void
TimedEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", ::libs::events_base::Event);
  arh& BOOST_SERIALIZATION_NVP (time_);

  self_correct ();
}
}   // namespace libs::events_base

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::TimedEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::TimedEvent);
