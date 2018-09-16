//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       command-code-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "command-code-event.hpp"

namespace libs { namespace igui_events { namespace events {

CommandCodeEvent::CommandCodeEvent (const Acessor& _ph, const std::string& _code) :
  code_ (_code)
{
  UASSERT (!code_.empty ());
  property_name_ = gen_get_mid ();
}


CommandCodeEvent::~CommandCodeEvent ()
{}


TypeEvents
CommandCodeEvent::get_type () const
{
  return TypeEvents::command_code;
}


std::string
CommandCodeEvent::get_code () const
{
  UASSERT (!code_.empty ());
  return code_;
}


void
CommandCodeEvent::set_code (const std::string& _id)
{
  UASSERT (!_id.empty ());
  code_ = _id;
  return;
}


::libs::events::IEvent::ptr
CommandCodeEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<CommandCodeEvent> (this, _deep);
}


void
CommandCodeEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (CommandCodeEvent);
  super::copy_int (_src);
  code_ = _dsrc->code_;
  return;
}


template <class Archive>
void
CommandCodeEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (code_);
  return;
}

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::CommandCodeEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::igui_events::events::CommandCodeEvent);
