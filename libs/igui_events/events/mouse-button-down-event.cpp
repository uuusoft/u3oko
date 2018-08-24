//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**   
\file       mouse-button-down-event.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "mouse-button-down-event.hpp"

namespace libs { namespace igui_events { namespace events {

MouseButtonDownEvent::MouseButtonDownEvent (const Acessor& _ph, const TypeMouseButton& _type, const utils::IPos::ptr& _pos) :
  type_ (_type),
  pos_ (_pos)
{
  property_name_ = gen_get_type_text_id ();
}


MouseButtonDownEvent::~MouseButtonDownEvent ()
{}


TypeEvents
MouseButtonDownEvent::get_type () const
{
  return TypeEvents::mbutton_down;
}


TypeMouseButton
MouseButtonDownEvent::get_type_button () const
{
  return type_;
}


void
MouseButtonDownEvent::set_type_button (const TypeMouseButton& _type)
{
  type_ = _type;
  return;
}


utils::IPos::ptr
MouseButtonDownEvent::get_pos () const
{
  return pos_;
}


void
MouseButtonDownEvent::set_pos (const utils::IPos::ptr& _pos)
{
  pos_ = _pos;
  return;
}


::libs::events::IEvent::ptr
MouseButtonDownEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<MouseButtonDownEvent> (this, _deep);
}


void
MouseButtonDownEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (MouseButtonDownEvent);
  super::copy_int (_src);
  type_ = _dsrc->type_;
  pos_  = _dsrc->pos_;
  return;
}


template <class Archive>
void
MouseButtonDownEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (type_);
  //ar & BOOST_SERIALIZATION_NVP( pos_ );
  return;
}

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::MouseButtonDownEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::igui_events::events::MouseButtonDownEvent);
