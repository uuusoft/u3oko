//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-data-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      Реализация базового класса события модуля обработки данных.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "base-data-event.hpp"

namespace libs { namespace imdata_events { namespace events {

BaseDataEvent::BaseDataEvent (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


BaseDataEvent::~BaseDataEvent ()
{}


void
BaseDataEvent::load_int (const base_functs::xml::itn& _node)
{
  ::libs::ievents::Event::load_int (_node);
  self_correct ();
  return;
}


::libs::events::IEvent::ptr
BaseDataEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<BaseDataEvent> (this, _deep);
}


void
BaseDataEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BaseDataEvent);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
BaseDataEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::BaseDataEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::imdata_events::events::BaseDataEvent);
