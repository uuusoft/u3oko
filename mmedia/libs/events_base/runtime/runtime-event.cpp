/**
\file       runtime-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "../events-base-includes_int.hpp"
#include "runtime-event.hpp"

namespace libs::events_base::runtime
{
RuntimeEvent::RuntimeEvent (const Acessor& pha)
{
}


auto
RuntimeEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return RuntimeEvent::gen_get_mid ();
}


auto
RuntimeEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< RuntimeEvent > (this, deep);
}


void
RuntimeEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< RuntimeEvent > (src);
  super::copy_int (src);
  //::libs::events_base::OpsStatusEvent::copy_int (src);
}


template< class Archive >
void
RuntimeEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoTimedEvent", ::libs::events_base::TimedEvent);
  // arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoOpsStatusEvent", ::libs::events_base::OpsStatusEvent);
  self_correct ();
}
}   // namespace libs::events_base::runtime

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::RuntimeEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::RuntimeEvent);
