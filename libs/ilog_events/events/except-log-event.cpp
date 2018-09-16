//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       except-log-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "except-log-event.hpp"

namespace libs { namespace ilog_events { namespace events {

ExceptLogEvent::ExceptLogEvent (const Acessor&, const AppllPartLogInfo& _appl, const std::string& _info) :
  InfoLogEvent (InfoLogEvent::Acessor (0), _appl, _info)
{
  property_name_ = gen_get_mid ();
}


ExceptLogEvent::~ExceptLogEvent ()
{}


::libs::events::IEvent::ptr
ExceptLogEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<ExceptLogEvent> (this, _deep);
}


void
ExceptLogEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ExceptLogEvent);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
ExceptLogEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::ExceptLogEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ilog_events::events::ExceptLogEvent);
