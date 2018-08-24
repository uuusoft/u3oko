//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       MouseButtonUpEvent.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "mouse-button-up-event.hpp"

namespace libs { namespace igui_events { namespace events {

MouseButtonUpEvent::MouseButtonUpEvent (const Acessor& _ph, const TypeMouseButton& _type, const utils::IPos::ptr& _pos) :
  type_ (_type),
  pos_ (_pos)
{
  property_name_ = gen_get_type_text_id ();
}


MouseButtonUpEvent::~MouseButtonUpEvent ()
{}


TypeEvents
MouseButtonUpEvent::get_type () const
{
  return TypeEvents::mbutton_up;
}


TypeMouseButton
MouseButtonUpEvent::get_type_button () const
{
  return type_;
}


void
MouseButtonUpEvent::set_type_button (const TypeMouseButton& _type)
{
  type_ = _type;
  return;
}


utils::IPos::ptr
MouseButtonUpEvent::get_pos () const
{
  return pos_;
}


void
MouseButtonUpEvent::set_pos (const utils::IPos::ptr& _pos)
{
  pos_ = _pos;
  return;
}


::libs::events::IEvent::ptr
MouseButtonUpEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<MouseButtonUpEvent> (this, _deep);
}


void
MouseButtonUpEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (MouseButtonUpEvent);
  super::copy_int (_src);
  type_ = _dsrc->type_;
  pos_  = _dsrc->pos_;
  return;
}


template <class Archive>
void
MouseButtonUpEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (type_);
  //ar & BOOST_SERIALIZATION_NVP( pos_ );
  return;
}

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::MouseButtonUpEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::igui_events::events::MouseButtonUpEvent);
