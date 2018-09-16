//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-storage-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       21.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "base-storage-event.hpp"

namespace libs { namespace istorage_events { namespace events {

BaseStorageEvent::BaseStorageEvent (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


BaseStorageEvent::~BaseStorageEvent ()
{}


::libs::events::IEvent::ptr
BaseStorageEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<BaseStorageEvent> (this, _deep);
}


void
BaseStorageEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BaseStorageEvent);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
BaseStorageEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::BaseStorageEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::istorage_events::events::BaseStorageEvent);
