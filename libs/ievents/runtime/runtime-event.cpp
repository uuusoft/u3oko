//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       runtime-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "runtime-event.hpp"

namespace libs { namespace ievents { namespace runtime {

RuntimeEvent::RuntimeEvent (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


RuntimeEvent::~RuntimeEvent ()
{}


::libs::events::IEvent::ptr
RuntimeEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<RuntimeEvent> (this, _deep);
}


void
RuntimeEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (RuntimeEvent);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
RuntimeEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}      // namespace libs::ievents::runtime

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::RuntimeEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::runtime::RuntimeEvent);
