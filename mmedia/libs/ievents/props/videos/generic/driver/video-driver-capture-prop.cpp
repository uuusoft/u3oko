/**
\file       video-driver-capture-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-driver-capture-prop.hpp"

namespace libs::ievents::props::videos::generic::driver
{
VideoDriverCaptureProp::VideoDriverCaptureProp (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


VideoDriverCaptureProp::~VideoDriverCaptureProp ()
{
}


::libs::events::IEvent::ptr
VideoDriverCaptureProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoDriverCaptureProp > (this, deep);
}


void
VideoDriverCaptureProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  capi_.type_resize_         = ::libs::ievents::props::videos::generic::convert::src2dst_from_raw_value (::libs::helpers::json::get_uint32 (obj.at ("type_resize")));
  capi_.type_capture_        = ::libs::ievents::props::videos::generic::driver::catch_rgn_from_raw_value (::libs::helpers::json::get_uint32 (obj.at ("type_capture")));
  capi_.fps_                 = ::libs::helpers::json::get_uint32 (obj.at ("capture_fps"));
  capi_.width_               = ::libs::helpers::json::get_uint32 (obj.at ("width"));
  capi_.height_              = ::libs::helpers::json::get_uint32 (obj.at ("height"));
  capi_.count_preload_frame_ = ::libs::helpers::json::get_uint32 (obj.at ("count_preload_frame"));
  capi_.mem_frames_cycle_    = ::libs::helpers::json::get_uint32 (obj.at ("mem_frames_cycle"));
  capi_.ms_delay_load_       = ::libs::helpers::json::get_uint32 (obj.at ("ms_delay_load"));
  capi_.mirror_x_            = obj.at ("mirror_x").as_bool ();
  capi_.mirror_y_            = obj.at ("mirror_y").as_bool ();
  capi_.rotation_            = ::libs::helpers::json::get_int32 (obj.at ("rotation"));
  capi_.focus_               = libs::ievents::props::videos::generic::driver::camera_focus_from_raw_value (::libs::helpers::json::get_uint32 (obj.at ("focus")));
  // EAI-BREAK-CHANGE 22.03.2026
  capi_.px_format_ = ::libs::helpers::uids::minor::from_raw_value (::libs::helpers::json::get_uint32 (obj.at ("px_format")));
  // capi_.px_format_           = ::libs::helpers::utils::cuuid_from_string (obj.at ("px_format").as_string ().c_str ());
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
  // EAI-BREAK-CHANGE 22.03.2026
  obj["px_format"] = U3_CAST_UINT32_FORCE (capi_.px_format_);
  // obj["px_format"]           = ::libs::helpers::utils::to_string (capi_.px_format_);
}


void
VideoDriverCaptureProp::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (VideoDriverCaptureProp);
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
VideoDriverCaptureProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (capi_.px_format_);
  ar& BOOST_SERIALIZATION_NVP (capi_.type_resize_);
  ar& BOOST_SERIALIZATION_NVP (capi_.type_capture_);
  ar& BOOST_SERIALIZATION_NVP (capi_.fps_);
  ar& BOOST_SERIALIZATION_NVP (capi_.width_);
  ar& BOOST_SERIALIZATION_NVP (capi_.height_);
  ar& BOOST_SERIALIZATION_NVP (capi_.count_preload_frame_);
  ar& BOOST_SERIALIZATION_NVP (capi_.mem_frames_cycle_);
  ar& BOOST_SERIALIZATION_NVP (capi_.ms_delay_load_);
  ar& BOOST_SERIALIZATION_NVP (capi_.mirror_x_);
  ar& BOOST_SERIALIZATION_NVP (capi_.mirror_y_);
  ar& BOOST_SERIALIZATION_NVP (capi_.rotation_);
  ar& BOOST_SERIALIZATION_NVP (capi_.focus_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::driver

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::driver::VideoDriverCaptureProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::driver::VideoDriverCaptureProp);
