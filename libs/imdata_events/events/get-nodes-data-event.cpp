//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       get-nodes-data-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "get-nodes-data-event.hpp"

namespace libs { namespace imdata_events { namespace events {

GetNodesDataEvent::GetNodesDataEvent (const Acessor& _ph, const id_path_type& _id_path, const nodes_list_type& _nodes) :
  BaseNodesDataEvent (BaseNodesDataEvent::Acessor (0), _id_path),
  nodes_ (_nodes)
{
  property_name_ = gen_get_mid ();
}


GetNodesDataEvent::~GetNodesDataEvent ()
{
}


const GetNodesDataEvent::nodes_list_type&
GetNodesDataEvent::get_nodes () const
{
  return nodes_;
}


void
GetNodesDataEvent::set_nodes (GetNodesDataEvent::nodes_list_type& _nodes)
{
  std::swap (nodes_, _nodes);
  return;
}


bool
GetNodesDataEvent::check () const
{
  UASSERT (super::check ());
  UASSERT (!nodes_.empty ());

  for (const auto& _node : nodes_)
    {
      if (!_node.check ())
        {
          UASSERT_SIGNAL ("failed check node GetNodesDataEvent");
          return false;
        }
    }

  return !super::check () || nodes_.empty () ? false : true;
}


::libs::events::IEvent::ptr
GetNodesDataEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<GetNodesDataEvent> (this, _deep);
}


void
GetNodesDataEvent::load_int (const base_functs::xml::itn& _node)
{
  super::load_int (_node);
  base_functs::xml::ritn _params = _node->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();
  self_correct ();
  return;
}


void
GetNodesDataEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (GetNodesDataEvent);
  super::copy_int (_src);
  nodes_ = _dsrc->nodes_;
  return;
}


template <class Archive>
void
GetNodesDataEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (nodes_);
  return;
}

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::GetNodesDataEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::imdata_events::events::GetNodesDataEvent);
