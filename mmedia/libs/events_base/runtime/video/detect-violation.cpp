/**
\file       detect-violation.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "detect-violation.hpp"

namespace libs::events_base::runtime::video
{
DetectViolation::DetectViolation (const Acessor& pha, const DetectViolations& state) :
  state_ (state)
{
}


auto
DetectViolation::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return DetectViolation::gen_get_mid ();
}


void
DetectViolation::sync_event_props (const DetectViolations& state)
{
  set_state (state);
}


void
DetectViolation::set_state (const DetectViolations& state)
{
  state_ = state;
}


auto
DetectViolation::get_state () const -> const DetectViolations&
{
  return state_;
}


auto
DetectViolation::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< DetectViolation > (this, deep);
}


void
DetectViolation::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< DetectViolation > (src);
  super::copy_int (src);
  state_ = dsrc->state_;
}


template< class Archive >
void
DetectViolation::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (state_);

  self_correct ();
}
}   // namespace libs::events_base::runtime::video

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::video::DetectViolation);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::video::DetectViolation);
