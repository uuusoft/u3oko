/**
\file       video-driver-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "video-driver-prop.hpp"

namespace libs::events_base::props::videos::generic::driver
{
VideoDriverProp::VideoDriverProp (const Acessor& pha)
{
  cat_dshow_ = ::libs::utility::uids::minor::get (::libs::utility::uids::minor::id_val::cat_video_device);
  sync_data ();
}


auto
VideoDriverProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return VideoDriverProp::gen_get_mid ();
}


auto
VideoDriverProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< VideoDriverProp > (this, deep);
}


void
VideoDriverProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  name_impl_dll_ = obj.at ("name_impl_dll").as_string ();
  cat_dshow_     = ::libs::utility::utils::cuuid_from_string (obj.at ("cat_dshow").as_string ().c_str ());
  device_name_   = ::libs::utility::json::get_string (obj.at ("device_name").as_string ());
  device_indx_   = ::libs::utility::json::get_uint32 (obj.at ("device_indx"));

  for (const auto& it : obj)
  {
    if (it.value ().is_string ())
    {
      ext_vals_[std::string (it.key ().data (), it.key ().size ())] = it.value ().as_string ();
    }
  }
}


void
VideoDriverProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["name_impl_dll"] = name_impl_dll_;
  obj["cat_dshow"]     = ::libs::utility::utils::to_string (cat_dshow_);
  obj["device_name"]   = ::libs::utility::json::to_string (device_name_);
  obj["device_indx"]   = device_indx_;

  for (const auto& val : ext_vals_)
  {
    obj[val.first] = val.second;
  }
}


void
VideoDriverProp::sync_data ()
{
  if (name_impl_dll_.empty ())
  {
#ifdef U3_OS_WIN32_DESKTOP
    name_impl_dll_ = "vss_dshow_vgen";
#elif defined(U3_OS_ANDROID)
    name_impl_dll_ = "vss_android_vgen";
#elif defined(U3_OS_GNU_LINUX)
    name_impl_dll_ = "vss_v4l2_vgen";
#elif defined(U3_OS_RASPBERRY)
    name_impl_dll_ = "vss_v4l2_vgen";
#elif defined(U3_OS_ORANGE_PI)
    name_impl_dll_ = "vss_v4l2_vgen";
#elif defined(U3_OS_MACX_DESKTOP)
    name_impl_dll_ = "vss_fake_vgen";
#else
#  error select OS
#endif
  }
}


void
VideoDriverProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoDriverProp > (src);
  super::copy_int (src);

  name_impl_dll_ = dsrc->name_impl_dll_;
  device_name_   = dsrc->device_name_;
  device_indx_   = dsrc->device_indx_;
  ext_vals_      = dsrc->ext_vals_;
}


template< class Archive >
void
VideoDriverProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);

  arh& BOOST_SERIALIZATION_NVP (name_impl_dll_);
  arh& BOOST_SERIALIZATION_NVP (device_name_);
  arh& BOOST_SERIALIZATION_NVP (device_indx_);
  arh& BOOST_SERIALIZATION_NVP (ext_vals_);

  self_correct ();
}
}   // namespace libs::events_base::props::videos::generic::driver

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::driver::VideoDriverProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::driver::VideoDriverProp);
