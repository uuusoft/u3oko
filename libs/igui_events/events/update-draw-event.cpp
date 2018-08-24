//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       UpdateDrawEvent.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "update-draw-event.hpp"

namespace libs { namespace igui_events { namespace events {

UpdateDrawEvent::UpdateDrawEvent (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


UpdateDrawEvent::~UpdateDrawEvent ()
{}


TypeEvents
UpdateDrawEvent::get_type () const
{
  return TypeEvents::update_draw;
}


::libs::events::IEvent::ptr
UpdateDrawEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<UpdateDrawEvent> (this, _deep);
}


void
UpdateDrawEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (UpdateDrawEvent);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
UpdateDrawEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::UpdateDrawEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::igui_events::events::UpdateDrawEvent);
