//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       wrapper-http-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ihttp_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "wrapper-http-event.hpp"

namespace libs { namespace ihttp_events { namespace events {

WrapperHttpEvent::WrapperHttpEvent (const Acessor& _ph, ::libs::events::IEvent::ptr _msg) :
  int_ (_msg)
{
  property_name_ = gen_get_type_text_id ();
}


WrapperHttpEvent::~WrapperHttpEvent ()
{}


::libs::events::IEvent::ptr
WrapperHttpEvent::get_msg () const
{
  return int_;
}


void
WrapperHttpEvent::set_msg (::libs::events::IEvent::ptr& _msg)
{
  int_ = _msg;
  return;
}


::libs::events::IEvent::ptr
WrapperHttpEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<WrapperHttpEvent> (this, _deep);
}


void
WrapperHttpEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (WrapperHttpEvent);
  super::copy_int (_src);
  int_ = _dsrc->int_;
  return;
}


template <class Archive>
void
WrapperHttpEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (int_);
  return;
}

}}}      // namespace libs::ihttp_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ihttp_events::events::WrapperHttpEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ihttp_events::events::WrapperHttpEvent);
