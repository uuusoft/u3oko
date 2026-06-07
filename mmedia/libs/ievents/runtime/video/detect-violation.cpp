/**
\file       detect-violation.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "detect-violation.hpp"

namespace libs::ievents::runtime::video
{
DetectViolation::DetectViolation (const Acessor& pha, const DetectViolations& state) :
  state_ (state)
{
  property_name_ = gen_get_mid ();
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


DetectViolations
DetectViolation::get_state () const
{
  return state_;
}


::libs::events::IEvent::ptr
DetectViolation::clone_int (const ::libs::events::Deeps& deep) const
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
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (state_);

  self_correct ();
}
}   // namespace libs::ievents::runtime::video

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::video::DetectViolation);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::video::DetectViolation);
