/**
\file       video-driver-capture-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "../../../../events-base-includes_int.hpp"
#include "video-driver-capture-prop.hpp"

namespace libs::events_base::props::videos::generic::driver
{
VideoDriverCaptureProp::VideoDriverCaptureProp (const Acessor& pha)
{
}


auto
VideoDriverCaptureProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return VideoDriverCaptureProp::gen_get_mid ();
}


auto
VideoDriverCaptureProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< VideoDriverCaptureProp > (this, deep);
}


void
VideoDriverCaptureProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  capi_.type_resize_         = convert::src2dst_from_raw_value (::libs::utility::json::get_uint32 (obj.at ("type_resize")));
  capi_.type_capture_        = catch_rgn_from_raw_value (::libs::utility::json::get_uint32 (obj.at ("type_capture")));
  capi_.fps_                 = ::libs::utility::json::get_uint32 (obj.at ("capture_fps"));
  capi_.width_               = ::libs::utility::json::get_uint32 (obj.at ("width"));
  capi_.height_              = ::libs::utility::json::get_uint32 (obj.at ("height"));
  capi_.count_preload_frame_ = ::libs::utility::json::get_uint32 (obj.at ("count_preload_frame"));
  capi_.mem_frames_cycle_    = ::libs::utility::json::get_uint32 (obj.at ("mem_frames_cycle"));
  capi_.ms_delay_load_       = ::libs::utility::json::get_uint32 (obj.at ("ms_delay_load"));
  capi_.mirror_x_            = obj.at ("mirror_x").as_bool ();
  capi_.mirror_y_            = obj.at ("mirror_y").as_bool ();
  capi_.rotation_            = ::libs::utility::json::get_int32 (obj.at ("rotation"));
  capi_.focus_               = libs::events_base::props::videos::generic::driver::camera_focus_from_raw_value (::libs::utility::json::get_uint32 (obj.at ("focus")));
  capi_.px_format_           = syn::minor::from_raw_value (::libs::utility::json::get_uint32 (obj.at ("px_format")));
}


void
VideoDriverCaptureProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["type_resize"]         = U3_CAST_UINT32_FORCE (capi_.type_resize_);
  obj["type_capture"]        = U3_CAST_UINT32_FORCE (capi_.type_capture_);
  obj["capture_fps"]         = capi_.fps_;
  obj["width"]               = capi_.width_;
  obj["height"]              = capi_.height_;
  obj["count_preload_frame"] = capi_.count_preload_frame_;
  obj["mem_frames_cycle"]    = capi_.mem_frames_cycle_;
  obj["ms_delay_load"]       = capi_.ms_delay_load_;
  obj["mirror_x"]            = capi_.mirror_x_;
  obj["mirror_y"]            = capi_.mirror_y_;
  obj["rotation"]            = capi_.rotation_;
  obj["focus"]               = U3_CAST_UINT32_FORCE (capi_.focus_);
  obj["px_format"]           = U3_CAST_UINT32_FORCE (capi_.px_format_);
}


void
VideoDriverCaptureProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoDriverCaptureProp > (src);
  super::copy_int (src);

  capi_.px_format_           = dsrc->capi_.px_format_;
  capi_.type_resize_         = dsrc->capi_.type_resize_;
  capi_.type_capture_        = dsrc->capi_.type_capture_;
  capi_.fps_                 = dsrc->capi_.fps_;
  capi_.width_               = dsrc->capi_.width_;
  capi_.height_              = dsrc->capi_.height_;
  capi_.count_preload_frame_ = dsrc->capi_.count_preload_frame_;
  capi_.mem_frames_cycle_    = dsrc->capi_.mem_frames_cycle_;
  capi_.ms_delay_load_       = dsrc->capi_.ms_delay_load_;
  capi_.mirror_x_            = dsrc->capi_.mirror_x_;
  capi_.mirror_y_            = dsrc->capi_.mirror_y_;
  capi_.rotation_            = dsrc->capi_.rotation_;
  capi_.focus_               = dsrc->capi_.focus_;
}


template< class Archive >
void
VideoDriverCaptureProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (capi_.px_format_);
  arh& BOOST_SERIALIZATION_NVP (capi_.type_resize_);
  arh& BOOST_SERIALIZATION_NVP (capi_.type_capture_);
  arh& BOOST_SERIALIZATION_NVP (capi_.fps_);
  arh& BOOST_SERIALIZATION_NVP (capi_.width_);
  arh& BOOST_SERIALIZATION_NVP (capi_.height_);
  arh& BOOST_SERIALIZATION_NVP (capi_.count_preload_frame_);
  arh& BOOST_SERIALIZATION_NVP (capi_.mem_frames_cycle_);
  arh& BOOST_SERIALIZATION_NVP (capi_.ms_delay_load_);
  arh& BOOST_SERIALIZATION_NVP (capi_.mirror_x_);
  arh& BOOST_SERIALIZATION_NVP (capi_.mirror_y_);
  arh& BOOST_SERIALIZATION_NVP (capi_.rotation_);
  arh& BOOST_SERIALIZATION_NVP (capi_.focus_);

  self_correct ();
}
}   // namespace libs::events_base::props::videos::generic::driver

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::driver::VideoDriverCaptureProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::driver::VideoDriverCaptureProp);
