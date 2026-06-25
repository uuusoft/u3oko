/**
\file       interf-correct-image-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "interf-correct-image-event.hpp"

namespace libs::ievents::runtime::interf
{
InterfCorrectImageEvent::InterfCorrectImageEvent (const Acessor& pha, const impl_ptr_type& impl) :
  impl_ (impl)
{
  property_name_ = gen_get_mid ();
}


InterfCorrectImageEvent::impl_ptr_type
InterfCorrectImageEvent::get_interface ()
{
  U3_ASSERT (!impl_.expired ());
  return impl_;
}


void
InterfCorrectImageEvent::set_interface (const impl_ptr_type& impl)
{
  impl_ = impl;
}


::libs::events::IEvent::ptr
InterfCorrectImageEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< InterfCorrectImageEvent > (this, deep);
}


void
InterfCorrectImageEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< InterfCorrectImageEvent > (src);
  super::copy_int (src);
  impl_ = dsrc->impl_;
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
template< class Archive >
void
InterfCorrectImageEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  arh& BOOST_SERIALIZATION_NVP (impl_);

  self_correct ();
}
#endif
}   // namespace libs::ievents::runtime::interf

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::interf::InterfCorrectImageEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::interf::InterfCorrectImageEvent);
#endif
