/**
\file       video-driver-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-driver-prop.hpp"

namespace libs::ievents::props::videos::generic::driver
{
VideoDriverProp::VideoDriverProp (const Acessor& ph) :
  device_indx_ (0)
{
  cat_dshow_     = ::libs::helpers::uids::minor::get (::libs::helpers::uids::minor::id_val::cat_video_device);
  property_name_ = gen_get_mid ();
  sync_data ();
}


VideoDriverProp::~VideoDriverProp ()
{
}


::libs::events::IEvent::ptr
VideoDriverProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoDriverProp > (this, deep);
}


void
VideoDriverProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  name_impl_dll_ = obj.at ("name_impl_dll").as_string ();
  cat_dshow_     = ::libs::helpers::utils::cuuid_from_string (obj.at ("cat_dshow").as_string ().c_str ());
  device_name_   = ::libs::helpers::json::get_string (obj.at ("device_name").as_string ());
  device_indx_   = ::libs::helpers::json::get_uint32 (obj.at ("device_indx"));

  for (auto it = obj.begin (); it != obj.end (); ++it)
  {
    if (it->value ().is_string ())
    {
      ext_vals_[std::string (it->key ().data (), it->key ().size ())] = it->value ().as_string ();
    }
  }
}


void
VideoDriverProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["name_impl_dll"] = name_impl_dll_;
  obj["cat_dshow"]     = ::libs::helpers::utils::to_string (cat_dshow_);
  obj["device_name"]   = ::libs::helpers::json::to_string (device_name_);
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
#if defined(U3_OS_WIN32_DESKTOP)
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
  U3_CHECK_COPY_EVENT (VideoDriverProp);
  super::copy_int (src);

  name_impl_dll_ = dsrc->name_impl_dll_;
  device_name_   = dsrc->device_name_;
  device_indx_   = dsrc->device_indx_;
  ext_vals_      = dsrc->ext_vals_;
}


template< class Archive >
void
VideoDriverProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);

  ar& BOOST_SERIALIZATION_NVP (name_impl_dll_);
  ar& BOOST_SERIALIZATION_NVP (device_name_);
  ar& BOOST_SERIALIZATION_NVP (device_indx_);
  ar& BOOST_SERIALIZATION_NVP (ext_vals_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::driver

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::driver::VideoDriverProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::driver::VideoDriverProp);
