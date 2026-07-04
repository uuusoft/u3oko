/**
\file       iwrap-base-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/
#include "../includes_int.hpp"
#include "iwrap-base-event.hpp"

namespace libs::events
{
IWrapBaseEvent::IWrapBaseEvent (const Acessor& pha, IEvent::ptr val) :
  int_ (std::move (val))
{
}


auto
IWrapBaseEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return IWrapBaseEvent::gen_get_mid ();
}


auto
IWrapBaseEvent::clone_int (const ::libs::events::Deeps& deep) const -> IEvent::ptr
{
  return ::libs::events::deep_clone< IWrapBaseEvent > (this, deep);
}


auto
IWrapBaseEvent::get_msg () const -> IEvent::ptr
{
  return int_;
}


void
IWrapBaseEvent::set_msg (IEvent::ptr& msg)
{
  int_ = msg;
}


void
IWrapBaseEvent::load_json_int (const ::boost::json::object& obj)
{
  // super::load_json_int (obj);
}


void
IWrapBaseEvent::save_json_int (::boost::json::object& obj) const
{
  // super::save_json_int (obj);
}


void
IWrapBaseEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< IWrapBaseEvent > (src);
  super::copy_int (src);
  int_ = dsrc->int_;
}


template< class Archive >
void
IWrapBaseEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("IEvent", super);
  arh& BOOST_SERIALIZATION_NVP (int_);
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::IWrapBaseEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events::IWrapBaseEvent);
