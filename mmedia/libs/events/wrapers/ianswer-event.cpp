/**
\file       ianswer-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/
#include "../includes_int.hpp"
#include "ianswer-event.hpp"

namespace libs::events
{
IAnswerEvent::IAnswerEvent (const Acessor& pha, IEvent::ptr val) :
  IWrapBaseEvent (IWrapBaseEvent::Acessor (0), std::move (val))
{
}


auto
IAnswerEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return IAnswerEvent::gen_get_mid ();
}


auto
IAnswerEvent::clone_int (const ::libs::events::Deeps& deep) const -> IEvent::ptr
{
  return ::libs::events::deep_clone< IAnswerEvent > (this, deep);
}


void
IAnswerEvent::copy_int (const IEvent::craw_ptr src)
{
  ::libs::iproperties::helpers::dbg_check_copy_event< IAnswerEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
IAnswerEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("IWrapBaseEvent", super);
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::IAnswerEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events::IAnswerEvent);
