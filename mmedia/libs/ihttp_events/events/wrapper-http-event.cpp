/**
\file       wrapper-http-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ihttp_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "wrapper-http-event.hpp"

namespace libs::ihttp_events::events
{
WrapperHttpEvent::WrapperHttpEvent (const Acessor& ph, ::libs::events::IEvent::ptr msg) :
  int_ (msg)
{
  property_name_ = gen_get_mid ();
}


WrapperHttpEvent::~WrapperHttpEvent ()
{
}


::libs::events::IEvent::ptr
WrapperHttpEvent::get_msg () const
{
  return int_;
}


void
WrapperHttpEvent::set_msg (::libs::events::IEvent::ptr& msg)
{
  int_ = msg;
}


::libs::events::IEvent::ptr
WrapperHttpEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< WrapperHttpEvent > (this, deep);
}


void
WrapperHttpEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (WrapperHttpEvent);
  super::copy_int (src);

  int_ = dsrc->int_;
}


template< class Archive >
void
WrapperHttpEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoTimedEvent", super);
  ar& BOOST_SERIALIZATION_NVP (int_);

  self_correct ();
}
}   // namespace libs::ihttp_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ihttp_events::events::WrapperHttpEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ihttp_events::events::WrapperHttpEvent);
