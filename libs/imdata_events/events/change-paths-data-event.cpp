//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       change-paths-data-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "change-paths-data-event.hpp"

namespace libs { namespace imdata_events { namespace events {

ChangePathsDataEvent::ChangePathsDataEvent (
  const Acessor&              _ph,
  const TypeChangePathAction& _action,
  const id_paths_list_type&   _paths) :
  action_ (_action),
  paths_ (_paths)
{
  property_name_ = gen_get_type_text_id ();
}


ChangePathsDataEvent::~ChangePathsDataEvent ()
{
  return;
}


const ChangePathsDataEvent::id_paths_list_type&
ChangePathsDataEvent::get_paths () const
{
  return paths_;
}


void
ChangePathsDataEvent::set_paths (ChangePathsDataEvent::id_paths_list_type& _paths)
{
  std::swap (paths_, _paths);
  return;
}


TypeChangePathAction
ChangePathsDataEvent::get_action () const
{
  return action_;
}


void
ChangePathsDataEvent::set_action (const TypeChangePathAction& _action)
{
  action_ = _action;
  return;
}


bool
ChangePathsDataEvent::check () const
{
  UASSERT (!paths_.empty ());
  return !paths_.empty ();
}


::libs::events::IEvent::ptr
ChangePathsDataEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<ChangePathsDataEvent> (this, _deep);
}


void
ChangePathsDataEvent::load_int (const base_functs::xml::itn& _node)
{
  super::load_int (_node);
#if 0
    base_functs::xml::ritn  _params = _node->children ("param");
    base_functs::xml::itn _param  = _params.begin ();

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
ChangePathsDataEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ChangePathsDataEvent);
  super::copy_int (_src);
  paths_  = _dsrc->paths_;
  action_ = _dsrc->action_;
  return;
}


template <class Archive>
void
ChangePathsDataEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (paths_);
  ar& BOOST_SERIALIZATION_NVP (action_);
  return;
}

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::ChangePathsDataEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::imdata_events::events::ChangePathsDataEvent);
