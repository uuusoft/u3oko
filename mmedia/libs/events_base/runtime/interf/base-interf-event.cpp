/**
\file       interf-correct-image-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "base-interf-event.hpp"

namespace libs::events_base::runtime::interf
{
BaseInterfEvent::BaseInterfEvent (const Acessor& pha) :
  active_ (false)
{
}


auto
BaseInterfEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BaseInterfEvent::gen_get_mid ();
}


void
BaseInterfEvent::set_active (bool active)
{
  active_ = active;
}


auto
BaseInterfEvent::is_active () const -> bool
{
  return active_;
}


void
BaseInterfEvent::set_available (bool enable)
{
  available_ = enable;
}


auto
BaseInterfEvent::is_available () const -> bool
{
  return available_;
}


auto
BaseInterfEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< BaseInterfEvent > (this, deep);
}


void
BaseInterfEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseInterfEvent > (src);
  super::copy_int (src);

  active_    = dsrc->active_;
  available_ = dsrc->available_;
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
template< class Archive >
void
BaseInterfEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP (super);
  arh& BOOST_SERIALIZATION_NVP (impl_);
  arh & active_;

  self_correct ();
}
#endif
}   // namespace libs::events_base::runtime::interf

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::interf::BaseInterfEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::interf::BaseInterfEvent);
#endif
