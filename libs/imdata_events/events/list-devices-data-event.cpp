//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       ListDevicesDataEvent.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "list-devices-data-event.hpp"

namespace libs { namespace imdata_events { namespace events {

ListDevicesDataEvent::ListDevicesDataEvent (const Acessor& _ph, const devices_group_type& _group, const devices_type& _devices) :
  group_ (_group),
  devices_ (_devices)
{
  property_name_ = gen_get_mid ();
}


ListDevicesDataEvent::~ListDevicesDataEvent ()
{
}


const ListDevicesDataEvent::devices_group_type&
ListDevicesDataEvent::get_group () const
{
  return group_;
}


const ListDevicesDataEvent::devices_type&
ListDevicesDataEvent::get_devices () const
{
  return devices_;
}


void
ListDevicesDataEvent::set_group (ListDevicesDataEvent::devices_group_type&& _src)
{
  std::swap (group_, _src);
  return;
}


void
ListDevicesDataEvent::set_devices (ListDevicesDataEvent::devices_type&& _src)
{
  std::swap (devices_, _src);
  return;
}


::libs::events::IEvent::ptr
ListDevicesDataEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<ListDevicesDataEvent> (this, _deep);
}


void
ListDevicesDataEvent::load_int (const base_functs::xml::itn& _node)
{
  super::load_int (_node);
  self_correct ();
  return;
}


void
ListDevicesDataEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ListDevicesDataEvent);
  super::copy_int (_src);
  group_   = _dsrc->group_;
  devices_ = _dsrc->devices_;
  return;
}


template <class Archive>
void
ListDevicesDataEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (group_);
  ar& BOOST_SERIALIZATION_NVP (devices_);
  return;
}

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::ListDevicesDataEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::imdata_events::events::ListDevicesDataEvent);
