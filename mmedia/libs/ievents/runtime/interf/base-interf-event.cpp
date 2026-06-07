/**
\file       interf-correct-image-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "base-interf-event.hpp"

namespace libs::ievents::runtime::interf
{
BaseInterfEvent::BaseInterfEvent (const Acessor& pha) :
  active_ (false)
{
  property_name_ = gen_get_mid ();
}


void
BaseInterfEvent::set_active (bool active)
{
  active_ = active;
}


bool
BaseInterfEvent::is_active () const
{
  return active_;
}


void
BaseInterfEvent::set_available (bool enable)
{
  available_ = enable;
}


bool
BaseInterfEvent::is_available () const
{
  return available_;
}


::libs::events::IEvent::ptr
BaseInterfEvent::clone_int (const ::libs::events::Deeps& deep) const
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

#ifdef U3_FAKE_DISABLE
template< class Archive >
void
BaseInterfEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  arh& BOOST_SERIALIZATION_NVP (impl_);
  arh & active_;

  self_correct ();
}
#endif
}   // namespace libs::ievents::runtime::interf

#ifdef U3_FAKE_DISABLE
BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::interf::BaseInterfEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::interf::BaseInterfEvent);
#endif
