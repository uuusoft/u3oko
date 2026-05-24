/**
\file       timed-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "timed-event.hpp"

namespace libs::ievents
{
TimedEvent::TimedEvent (const Acessor& ph) :
  time_ (boost::posix_time::microsec_clock::universal_time ())
{
  property_name_ = gen_get_mid ();
}


TimedEvent::~TimedEvent ()
{
}


::libs::events::IEvent::ptr
TimedEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< TimedEvent > (this, deep);
}


boost::posix_time::ptime
TimedEvent::get_time () const
{
  return time_;
}


void
TimedEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (TimedEvent);
  super::copy_int (src);
  time_ = dsrc->time_;
}


template< class Archive >
void
TimedEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", ::libs::ievents::Event);
  ar& BOOST_SERIALIZATION_NVP (time_);

  self_correct ();
}
}   // namespace libs::ievents

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::TimedEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::TimedEvent);
