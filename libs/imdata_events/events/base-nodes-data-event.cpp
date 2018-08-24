//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       BaseNodesDataEvent.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "base-nodes-data-event.hpp"

namespace libs { namespace imdata_events { namespace events {

BaseNodesDataEvent::BaseNodesDataEvent (const Acessor& _ph, const id_path_type& _id_path) :
  id_path_ (_id_path)
{
  property_name_ = gen_get_type_text_id ();

  return;
}


BaseNodesDataEvent::~BaseNodesDataEvent ()
{
  return;
}


const BaseNodesDataEvent::id_path_type&
BaseNodesDataEvent::get_id_path () const
{
  return id_path_;
}


void
BaseNodesDataEvent::set_id_path (id_path_type&& _id)
{
  std::swap (id_path_, _id);
  return;
}


bool
BaseNodesDataEvent::check () const
{
  UASSERT (!id_path_.empty ());
  return id_path_.empty () ? false : true;
}


::libs::events::IEvent::ptr
BaseNodesDataEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<BaseNodesDataEvent> (this, _deep);
}


void
BaseNodesDataEvent::load_int (const base_functs::xml::itn& _node)
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
BaseNodesDataEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BaseNodesDataEvent);
  super::copy_int (_src);
  id_path_ = _dsrc->id_path_;
  return;
}


template <class Archive>
void
BaseNodesDataEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (id_path_);
  return;
}

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::BaseNodesDataEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::imdata_events::events::BaseNodesDataEvent);
