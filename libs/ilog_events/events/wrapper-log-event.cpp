//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       wrapper-log-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "wrapper-log-event.hpp"

namespace libs { namespace ilog_events { namespace events {

WrapperLogEvent::WrapperLogEvent (const Acessor&, ::libs::events::IEvent::ptr _msg) :
  int_ (_msg)
{
  property_name_ = gen_get_mid ();
}


WrapperLogEvent::~WrapperLogEvent ()
{}


::libs::events::IEvent::ptr
WrapperLogEvent::get_msg () const
{
  return int_;
}


void
WrapperLogEvent::set_msg (::libs::events::IEvent::ptr& _msg)
{
  int_ = _msg;
  return;
}


::libs::events::IEvent::ptr
WrapperLogEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<WrapperLogEvent> (this, _deep);
}


void
WrapperLogEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (WrapperLogEvent);
  super::copy_int (_src);
  int_ = _dsrc->int_;
  return;
}


template <class Archive>
void
WrapperLogEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (int_);
  return;
}

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::WrapperLogEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ilog_events::events::WrapperLogEvent);
