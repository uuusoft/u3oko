//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       ievent.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "ievent.hpp"

namespace libs { namespace events {

IEvent::IEvent () :
  state_ (UsingStateEvent::disabled)
{}


IEvent::~IEvent ()
{}


IEvent::ptr
IEvent::clone (const ::libs::events::DeepEventCloneType& _deep) const
{
  return clone_int (_deep);
}


void
IEvent::copy (const IEvent::craw_ptr _src)
{
  return copy_int (_src);
}


const IEvent::hid_type&
IEvent::get_mid () const
{
  UASSERT (!property_name_.empty ());
  return property_name_;
}


bool
IEvent::check_node (const base_functs::xml::itn& _node)
{
  XULOG_TRACE ("try check_node, " << property_name_);
  pugi::xml_attribute _name_property = _node->attribute ("name");

  if (!_name_property)
    {
      return false;
    }

  if (property_name_ != _name_property.as_string ())
    {
      XULOG_TRACE ("failed check_node, {" << property_name_ << "} != {" << _name_property.as_string () << "}");
      return false;
    }

  if (!check_node_int (_node))
    {
      XULOG_WARNING ("failed check_node, {" << property_name_ << "} int");
      UASSERT_SIGNAL ("failed");
      return false;
    }
  return true;
}


const UsingStateEvent&
IEvent::get_using_state () const
{
  return state_;
}


void
IEvent::load (const base_functs::xml::itn& _prop)
{
  UASSERT (check_node (_prop));
  load_int (_prop);
  return;
}


void
IEvent::copy_int (const IEvent::craw_ptr _src)
{
  //IEvent::operator= (*_src);
  property_name_ = _src->property_name_;
  state_         = _src->state_;
  return;
}


void
IEvent::self_correct ()
{
  self_correct_int ();
  return;
}


void
IEvent::self_correct_int ()
{
  return;
}


void
IEvent::sync_txt2val ()
{
  sync_txt2val_int ();
  return;
}


void
IEvent::sync_txt2val_int ()
{
  return;
}


void
IEvent::sync_val2txt ()
{
  sync_val2txt_int ();
  return;
}


void
IEvent::sync_val2txt_int ()
{
  return;
}


bool
IEvent::is_failed_int () const
{
  return false;
}


template <class Archive>
void
IEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (property_name_);
  ar& BOOST_SERIALIZATION_NVP (state_);
  return;
}

}}      // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::IEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::events::IEvent);
