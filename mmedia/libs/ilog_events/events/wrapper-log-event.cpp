/**
\file       wrapper-log-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "wrapper-log-event.hpp"

namespace libs::ilog_events::events
{
WrapperLogEvent::WrapperLogEvent (const Acessor&, ::libs::events::IEvent::ptr msg) :
  int_ (msg)
{
  property_name_ = gen_get_mid ();
}


WrapperLogEvent::~WrapperLogEvent ()
{
}


::libs::events::IEvent::ptr
WrapperLogEvent::get_msg () const
{
  return int_;
}


void
WrapperLogEvent::set_msg (::libs::events::IEvent::ptr& msg)
{
  int_ = msg;
}


::libs::events::IEvent::ptr
WrapperLogEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< WrapperLogEvent > (this, deep);
}


void
WrapperLogEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (WrapperLogEvent);
  super::copy_int (src);
  int_ = dsrc->int_;
}


template< class Archive >
void
WrapperLogEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoTimedEvent", super);
  ar& BOOST_SERIALIZATION_NVP (int_);

  self_correct ();
}
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::WrapperLogEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ilog_events::events::WrapperLogEvent);
