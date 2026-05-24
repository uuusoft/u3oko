/**
\file       list-devices-data-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "list-devices-data-event.hpp"

namespace libs::imdata_events::events
{
DataSourceInfo::DataSourceInfo (
  const std::string& name,
  const DataSources& type,
  int                max_count,
  int                number) :
  name_ (name),
  type_ (type),
  max_count_ (max_count),
  number_ (number)
{
}


DataSourceInfo::~DataSourceInfo ()
{
}


template< class Archive >
void
DataSourceInfo::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (name_);
  ar& BOOST_SERIALIZATION_NVP (type_);
  ar& BOOST_SERIALIZATION_NVP (max_count_);
  ar& BOOST_SERIALIZATION_NVP (number_);
}


ListDevicesDataEvent::ListDevicesDataEvent (
  const Acessor&           ph,
  const src_names_type&    group,
  const src_devinfos_type& devices) :
  source_dll_names_ (group),
  dlls_devices_ (devices)
{
  property_name_ = gen_get_mid ();
}


ListDevicesDataEvent::~ListDevicesDataEvent ()
{
}


const ListDevicesDataEvent::src_names_type&
ListDevicesDataEvent::get_source_dll_names () const
{
  return source_dll_names_;
}


const ListDevicesDataEvent::src_infos_type&
ListDevicesDataEvent::get_devices_for_dll (std::size_t indx) const
{
  return dlls_devices_[indx];
}


void
ListDevicesDataEvent::set_source_dll_names (ListDevicesDataEvent::src_names_type&& src)
{
  std::swap (source_dll_names_, src);
  dlls_devices_.resize (source_dll_names_.size ());
}


void
ListDevicesDataEvent::set_devices_for_dll (
  std::size_t                            indx,
  ListDevicesDataEvent::src_infos_type&& src)
{
  std::swap (dlls_devices_[indx], src);
}


::libs::events::IEvent::ptr
ListDevicesDataEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ListDevicesDataEvent > (this, deep);
}


void
ListDevicesDataEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "ListDevicesDataEvent::load_json_int::not support");
}


void
ListDevicesDataEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  auto& sources = obj["source_dll_names"].emplace_array ();
  for (const auto& source : source_dll_names_)
  {
    sources.push_back (::boost::json::value (source));
  }

  auto& dlls_devices = obj["dlls_devices"].emplace_array ();
  for (const auto& dll_devices : dlls_devices_)
  {
    ::boost::json::array devices;
    for (const auto& dll_device : dll_devices)
    {
      devices.push_back (::boost::json::value (dll_device.name_));
    }
    dlls_devices.push_back (devices);
  }
}


void
ListDevicesDataEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (ListDevicesDataEvent);
  super::copy_int (src);
  source_dll_names_ = dsrc->source_dll_names_;
  dlls_devices_     = dsrc->dlls_devices_;
}


template< class Archive >
void
ListDevicesDataEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoimdata_eventsoeventsoBaseDataEvent", super);
  ar& BOOST_SERIALIZATION_NVP (source_dll_names_);
  ar& BOOST_SERIALIZATION_NVP (dlls_devices_);

  self_correct ();
}
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::DataSourceInfo);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::imdata_events::events::DataSourceInfo);

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::ListDevicesDataEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::imdata_events::events::ListDevicesDataEvent);
