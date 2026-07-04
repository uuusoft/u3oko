/**
\file       list-devices-data-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_media
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "list-devices-data-event.hpp"

namespace libs::events_media::events
{
DataSourceInfo::DataSourceInfo (
  std::string        name,
  const DataSources& type,
  int                max_count,
  int                number) :
  name_ (std::move (name)),
  type_ (type),
  max_count_ (max_count),
  number_ (number)
{
}


template< class Archive >
void
DataSourceInfo::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (name_);
  arh& BOOST_SERIALIZATION_NVP (type_);
  arh& BOOST_SERIALIZATION_NVP (max_count_);
  arh& BOOST_SERIALIZATION_NVP (number_);
}


ListDevicesDataEvent::ListDevicesDataEvent (
  const Acessor&    ph,
  src_names_type    group,
  src_devinfos_type devices) :
  source_dll_names_ (std::move (group)),
  dlls_devices_ (std::move (devices))
{
}


auto
ListDevicesDataEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ListDevicesDataEvent::gen_get_mid ();
}


auto
ListDevicesDataEvent::get_source_dll_names () const -> const ListDevicesDataEvent::src_names_type&
{
  return source_dll_names_;
}


auto
ListDevicesDataEvent::get_devices_for_dll (std::size_t indx) const -> const ListDevicesDataEvent::src_infos_type&
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


auto
ListDevicesDataEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
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
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ListDevicesDataEvent > (src);
  super::copy_int (src);

  source_dll_names_ = dsrc->source_dll_names_;
  dlls_devices_     = dsrc->dlls_devices_;
}


template< class Archive >
void
ListDevicesDataEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_mediaoeventsoBaseDataEvent", super);
  arh& BOOST_SERIALIZATION_NVP (source_dll_names_);
  arh& BOOST_SERIALIZATION_NVP (dlls_devices_);

  self_correct ();
}
}   // namespace libs::events_media::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_media::events::DataSourceInfo);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_media::events::DataSourceInfo);

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_media::events::ListDevicesDataEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_media::events::ListDevicesDataEvent);
