//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       wrapper-storage-event.cpp
\date       21.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "wrapper-storage-event.hpp"

namespace libs { namespace istorage_events { namespace events {

WrapperStorageEvent::WrapperStorageEvent (const Acessor& _ph, ::libs::events::IEvent::ptr _msg) :
  int_ (_msg)
{
  property_name_ = gen_get_mid ();
}


WrapperStorageEvent::~WrapperStorageEvent ()
{}


::libs::events::IEvent::ptr
WrapperStorageEvent::get_msg () const
{
  return int_;
}


void
WrapperStorageEvent::set_msg (::libs::events::IEvent::ptr& _msg)
{
  int_ = _msg;
  return;
}


::libs::events::IEvent::ptr
WrapperStorageEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<WrapperStorageEvent> (this, _deep);
}


void
WrapperStorageEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (WrapperStorageEvent);
  super::copy_int (_src);
  int_ = _dsrc->int_;
  return;
}


template <class Archive>
void
WrapperStorageEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (int_);
  return;
}

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::WrapperStorageEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::istorage_events::events::WrapperStorageEvent);
