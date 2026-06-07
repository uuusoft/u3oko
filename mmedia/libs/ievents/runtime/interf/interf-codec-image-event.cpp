/**
\file       interf-codec-image-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "interf-codec-image-event.hpp"

namespace libs::ievents::runtime::interf
{
InterfCodecImageEvent::InterfCodecImageEvent (const Acessor& pha, const impl_ptr_type& impl) :
  impl_ (impl)
{
  property_name_ = gen_get_mid ();
}


InterfCodecImageEvent::impl_ptr_type
InterfCodecImageEvent::get_interface ()
{
  U3_ASSERT (!impl_.expired ());
  return impl_;
}


void
InterfCodecImageEvent::set_interface (const impl_ptr_type& impl)
{
  impl_ = impl;
}


::libs::events::IEvent::ptr
InterfCodecImageEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< InterfCodecImageEvent > (this, deep);
}


void
InterfCodecImageEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< InterfCodecImageEvent > (src);
  super::copy_int (src);
  impl_ = dsrc->impl_;
}

#ifdef U3_FAKE_DISABLE
template< class Archive >
void
InterfCodecImageEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  arh& BOOST_SERIALIZATION_NVP (impl_);

  self_correct ();
}
#endif
}   // namespace libs::ievents::runtime::interf

#ifdef U3_FAKE_DISABLE
BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::interf::InterfCodecImageEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::interf::InterfCodecImageEvent);
#endif
