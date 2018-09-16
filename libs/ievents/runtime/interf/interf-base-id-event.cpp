//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       interf-base-id-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       19.07.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "interf-base-id-event.hpp"

namespace libs { namespace ievents { namespace runtime { namespace interf {

InterfBaseIdEvent::InterfBaseIdEvent (const Acessor& _ph, const impl_ptr_type& _impl) :
  impl_ (_impl)
{
  property_name_ = gen_get_mid ();
}


InterfBaseIdEvent::~InterfBaseIdEvent ()
{}


InterfBaseIdEvent::impl_ptr_type
InterfBaseIdEvent::get_interface ()
{
  UASSERT (!impl_.expired ());
  return impl_;
}


void
InterfBaseIdEvent::set_interface (const impl_ptr_type& _impl)
{
  impl_ = _impl;
  return;
}


::libs::events::IEvent::ptr
InterfBaseIdEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<InterfBaseIdEvent> (this, _deep);
}


void
InterfBaseIdEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (InterfBaseIdEvent);
  super::copy_int (_src);
  impl_ = _dsrc->impl_;
  return;
}

#if 0
  template<class Archive>
  void InterfBaseIdEvent::serialize (Archive & ar, const unsigned int /* file_version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( super );
    ar & BOOST_SERIALIZATION_NVP( impl_ );
    return;
  }
#endif
}}}}      // namespace libs::ievents::runtime::interf
#if 0
BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::runtime::interf::InterfBaseIdEvent );
SERIALIZE_TYPE_TO_ARCHIVES( ::libs::ievents::runtime::interf::InterfBaseIdEvent );
#endif
