/**
\file       interf-base-id-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       19.07.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "interf-base-id-event.hpp"

namespace libs::ievents::runtime::interf
{
InterfBaseIdEvent::InterfBaseIdEvent (const Acessor& ph, const impl_ptr_type& impl) :
  impl_ (impl)
{
  property_name_ = gen_get_mid ();
}


InterfBaseIdEvent::~InterfBaseIdEvent ()
{
}


InterfBaseIdEvent::impl_ptr_type
InterfBaseIdEvent::get_interface ()
{
  U3_ASSERT (!impl_.expired ());
  return impl_;
}


void
InterfBaseIdEvent::set_interface (const impl_ptr_type& impl)
{
  impl_ = impl;
}


::libs::events::IEvent::ptr
InterfBaseIdEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< InterfBaseIdEvent > (this, deep);
}


void
InterfBaseIdEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (InterfBaseIdEvent);
  super::copy_int (src);
  impl_ = dsrc->impl_;
}

#if 0
template< class Archive >
void
InterfBaseIdEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (impl_);

  self_correct ();
}
#endif
}   // namespace libs::ievents::runtime::interf

#if 0
BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::runtime::interf::InterfBaseIdEvent );
U3_BOOST_SERIALIZE_ALL_ARCHIVES( ::libs::ievents::runtime::interf::InterfBaseIdEvent );
#endif
