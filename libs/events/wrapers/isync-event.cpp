//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       isync-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "isync-event.hpp"

namespace libs { namespace events {

ISyncEvent::ISyncEvent (const Acessor& _ph, IEvent::ptr _int) :
  IWrapBaseEvent (IWrapBaseEvent::Acessor (0), _int)
{
  property_name_ = gen_get_mid ();
}


ISyncEvent::~ISyncEvent ()
{}


IEvent::ptr
ISyncEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<ISyncEvent> (this, _deep);
}


void
ISyncEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ISyncEvent);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
ISyncEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}      // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::ISyncEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::events::ISyncEvent);
