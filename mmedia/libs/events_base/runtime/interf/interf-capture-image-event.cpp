/**
\file       interf-capture-image-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       17.08.2018
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "interf-capture-image-event.hpp"

namespace libs::events_base::runtime::interf
{
InterfCaptureImageEvent::InterfCaptureImageEvent (const Acessor& pha, impl_ptr_type impl) :
  impl_ (std::move (impl))
{
}


auto
InterfCaptureImageEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return InterfCaptureImageEvent::gen_get_mid ();
}


auto
InterfCaptureImageEvent::get_interface () -> InterfCaptureImageEvent::impl_ptr_type
{
  U3_ASSERT (!impl_.expired ());
  return impl_;
}


void
InterfCaptureImageEvent::set_interface (const impl_ptr_type& impl)
{
  impl_ = impl;
}


auto
InterfCaptureImageEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< InterfCaptureImageEvent > (this, deep);
}


void
InterfCaptureImageEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< InterfCaptureImageEvent > (src);
  super::copy_int (src);
  impl_ = dsrc->impl_;
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
template< class Archive >
void
InterfCaptureImageEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP (super);
  arh& BOOST_SERIALIZATION_NVP (impl_);

  self_correct ();
}
#endif
}   // namespace libs::events_base::runtime::interf

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::interf::InterfCaptureImageEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::interf::InterfCaptureImageEvent);
#endif
