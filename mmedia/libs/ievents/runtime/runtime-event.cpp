/**
\file       runtime-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "runtime-event.hpp"

namespace libs::ievents::runtime
{
RuntimeEvent::RuntimeEvent (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
RuntimeEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< RuntimeEvent > (this, deep);
}


void
RuntimeEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< RuntimeEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
RuntimeEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoTimedEvent", super);
  self_correct ();
}
}   // namespace libs::ievents::runtime

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::RuntimeEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::RuntimeEvent);
