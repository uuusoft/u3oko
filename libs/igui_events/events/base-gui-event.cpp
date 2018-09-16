//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-gui-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "base-gui-event.hpp"
#include "type-events.hpp"

namespace libs { namespace igui_events { namespace events {

BaseGUIEvent::BaseGUIEvent (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


BaseGUIEvent::~BaseGUIEvent ()
{}


bool
BaseGUIEvent::check_node_int (const base_functs::xml::itn& /*_node*/)
{
  return false;
}


void
BaseGUIEvent::load_int (const base_functs::xml::itn& _node)
{
  super::load_int (_node);
  self_correct ();
  return;
}


TypeEvents
BaseGUIEvent::get_type () const
{
  return TypeEvents::mem_block;
}


::libs::events::IEvent::ptr
BaseGUIEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<BaseGUIEvent> (this, _deep);
}


void
BaseGUIEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BaseGUIEvent);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
BaseGUIEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::BaseGUIEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::igui_events::events::BaseGUIEvent);
