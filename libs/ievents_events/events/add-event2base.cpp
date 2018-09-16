//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       add-event2base.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       09.09.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "add-event2base.hpp"

namespace libs { namespace ievents_events { namespace events {

AddEvent2Base::AddEvent2Base (const Acessor& _ph, const ::libs::events::IEvent::ptr& _obj) :
  int_ (_obj)
{
  property_name_ = gen_get_mid ();
}


AddEvent2Base::~AddEvent2Base ()
{}


void
AddEvent2Base::set_event (::libs::events::IEvent::ptr& _obj)
{
  int_ = _obj;
  return;
}


::libs::events::IEvent::ptr
AddEvent2Base::get_event () const
{
  return int_;
}


void
AddEvent2Base::set_object_id (const object_id_type& _id)
{
  object_id_ = _id;
  return;
}


const AddEvent2Base::object_id_type&
AddEvent2Base::get_object_id () const
{
  return object_id_;
}


void
AddEvent2Base::set_machine_id (const machine_id_type& _id)
{
  machine_id_ = _id;
  return;
}


const AddEvent2Base::machine_id_type&
AddEvent2Base::get_machine_id () const
{
  return machine_id_;
}


::libs::events::IEvent::ptr
AddEvent2Base::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<AddEvent2Base> (this, _deep);
}


void
AddEvent2Base::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (AddEvent2Base);
  super::copy_int (_src);
  machine_id_ = _dsrc->machine_id_;
  object_id_  = _dsrc->object_id_;
  int_        = _dsrc->int_;
  return;
}


template <class Archive>
void
AddEvent2Base::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (machine_id_);
  ar& BOOST_SERIALIZATION_NVP (object_id_);
  ar& BOOST_SERIALIZATION_NVP (int_);
  return;
}

}}}      // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents_events::events::AddEvent2Base);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents_events::events::AddEvent2Base);
