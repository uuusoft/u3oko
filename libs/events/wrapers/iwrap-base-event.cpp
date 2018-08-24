//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       iwrap-base-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "iwrap-base-event.hpp"

namespace libs { namespace events {

IWrapBaseEvent::IWrapBaseEvent (const Acessor& _ph, IEvent::ptr _int) :
  int_ (_int)
{
  property_name_ = gen_get_type_text_id ();
}


IWrapBaseEvent::~IWrapBaseEvent ()
{}


IEvent::ptr
IWrapBaseEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<IWrapBaseEvent> (this, _deep);
}


IEvent::ptr
IWrapBaseEvent::get_msg () const
{
  return int_;
}


void
IWrapBaseEvent::set_msg (IEvent::ptr& _msg)
{
  int_ = _msg;
  return;
}


bool
IWrapBaseEvent::check_node_int (const base_functs::xml::itn& _node)
{
  return true;
}


void
IWrapBaseEvent::load_int (const base_functs::xml::itn& _prop)
{
  self_correct ();
  return;
}


void
IWrapBaseEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (IWrapBaseEvent);
  super::copy_int (_src);
  int_ = _dsrc->int_;
  return;
}


template <class Archive>
void
IWrapBaseEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (int_);
  return;
}

}}      // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::IWrapBaseEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::events::IWrapBaseEvent);
