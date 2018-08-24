//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       change-node-data-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "change-node-data-event.hpp"

namespace libs { namespace imdata_events { namespace events {

ChangeNodeDataEvent::ChangeNodeDataEvent (
  const Acessor&                  _ph,
  const TypeChangeNodePathAction& _action,
  const id_path_type&             _id_path,
  const id_node_path_type&        _id_node,
  const events_list_type&         _events) :

  BaseNodesDataEvent (BaseNodesDataEvent::Acessor (0), _id_path),
  action_ (_action),
  id_node_ (_id_node),
  events_ (_events)
{
  property_name_ = gen_get_type_text_id ();
}


ChangeNodeDataEvent::~ChangeNodeDataEvent ()
{
  return;
}


const ChangeNodeDataEvent::id_node_path_type&
ChangeNodeDataEvent::get_node () const
{
  return id_node_;
}


void
ChangeNodeDataEvent::set_node (const id_node_path_type& _node)
{
  id_node_ = _node;
  return;
}


TypeChangeNodePathAction
ChangeNodeDataEvent::get_action () const
{
  return action_;
}


void
ChangeNodeDataEvent::set_action (const TypeChangeNodePathAction& _action)
{
  action_ = _action;
  return;
}


const ChangeNodeDataEvent::events_list_type&
ChangeNodeDataEvent::get_events () const
{
  return events_;
}


void
ChangeNodeDataEvent::set_events (const ChangeNodeDataEvent::events_list_type& _events)
{
  events_ = _events;
  return;
}


bool
ChangeNodeDataEvent::check () const
{
  return !super::check () || !id_node_.check () ? false : true;
}


::libs::events::IEvent::ptr
ChangeNodeDataEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<ChangeNodeDataEvent> (this, _deep);
}


void
ChangeNodeDataEvent::load_int (const base_functs::xml::itn& _node)
{
  super::load_int (_node);

  base_functs::xml::ritn _params = _node->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();
#if 0
    while ( _param != _params.end () )
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");

      if ( _name_param && _val_param)
      {}

      ++_param;
    }
#endif
  self_correct ();
  return;
}


void
ChangeNodeDataEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ChangeNodeDataEvent);
  super::copy_int (_src);

  id_node_ = _dsrc->id_node_;
  action_  = _dsrc->action_;
  events_  = _dsrc->events_;
  return;
}


template <class Archive>
void
ChangeNodeDataEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (id_node_);
  ar& BOOST_SERIALIZATION_NVP (action_);
  ar& BOOST_SERIALIZATION_NVP (events_);
  return;
}

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::ChangeNodeDataEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::imdata_events::events::ChangeNodeDataEvent);
