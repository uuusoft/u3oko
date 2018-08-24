//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-buff-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "video-buff-event.hpp"

namespace libs { namespace igui_events { namespace events {

VideoBuffEvent::VideoBuffEvent (const Acessor& _ph, const Buffs::ptr& _buff, int _id) :
  buff_ (_buff),
  id_ (_id)
{
  property_name_ = gen_get_type_text_id ();
}


VideoBuffEvent::~VideoBuffEvent ()
{}


TypeEvents
VideoBuffEvent::get_type () const
{
  return TypeEvents::video_buff;
}

const Buffs::ptr
VideoBuffEvent::get_buff () const
{
  UASSERT (buff_);
  return buff_;
}


void
VideoBuffEvent::set_buff (Buffs::ptr& _buff)
{
  buff_ = _buff;
  return;
}


void
VideoBuffEvent::set_id (int _id)
{
  id_ = _id;
  return;
}


int
VideoBuffEvent::get_id () const
{
  return id_;
}


::libs::events::IEvent::ptr
VideoBuffEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<VideoBuffEvent> (this, _deep);
}


void
VideoBuffEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoBuffEvent);
  super::copy_int (_src);
  buff_ = _dsrc->buff_;
  id_   = _dsrc->id_;
  return;
}


template <class Archive>
void
VideoBuffEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  //ar & BOOST_SERIALIZATION_NVP( hmem_ );
  ar& BOOST_SERIALIZATION_NVP (id_);
  UUU_THROW_EXCEPTION ("try serializate VideoBuffEvent");
  return;
}

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::VideoBuffEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::igui_events::events::VideoBuffEvent);
