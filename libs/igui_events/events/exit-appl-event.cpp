//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       ExitApplEvent.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "exit-appl-event.hpp"

namespace libs { namespace igui_events { namespace events {

ExitApplEvent::ExitApplEvent (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


ExitApplEvent::~ExitApplEvent ()
{}


TypeEvents
ExitApplEvent::get_type () const
{
  return TypeEvents::exit_appl;
}


::libs::events::IEvent::ptr
ExitApplEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<ExitApplEvent> (this, _deep);
}


void
ExitApplEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ExitApplEvent);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
ExitApplEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::ExitApplEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::igui_events::events::ExitApplEvent);
