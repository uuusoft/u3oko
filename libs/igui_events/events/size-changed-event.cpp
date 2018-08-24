//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       SizeChangedEvent.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "size-changed-event.hpp"

namespace libs { namespace igui_events { namespace events {

SizeChangedEvent::SizeChangedEvent (const Acessor& _ph, const ::libs::igui_events::utils::ISize::ptr& _size) :
  size_ (_size)
{
  property_name_ = gen_get_type_text_id ();
}


SizeChangedEvent::~SizeChangedEvent ()
{}


TypeEvents
SizeChangedEvent::get_type () const
{
  return TypeEvents::size_changed;
}


::libs::igui_events::utils::ISize::ptr
SizeChangedEvent::get_size () const
{
  return size_;
}


void
SizeChangedEvent::set_size (const ::libs::igui_events::utils::ISize::ptr& _size)
{
  size_ = _size;
  return;
}


::libs::events::IEvent::ptr
SizeChangedEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<SizeChangedEvent> (this, _deep);
}


void
SizeChangedEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (SizeChangedEvent);
  super::copy_int (_src);
  size_ = _dsrc->size_;
  return;
}


template <class Archive>
void
SizeChangedEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  //ar & BOOST_SERIALIZATION_NVP( size_ );
  return;
}

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::SizeChangedEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::igui_events::events::SizeChangedEvent);
