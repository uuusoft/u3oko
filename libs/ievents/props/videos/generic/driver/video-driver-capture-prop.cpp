//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-driver-capture-prop.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-driver-capture-prop.hpp"
//parameter_awb_mode
//parameter_flicker_avoid
//parameter_flash
//parameter_redeye
//parameter_focal_lengths
//parameter_exposure_comp
//parameter_zoom
//parameter_mirror
//parameter_exposure_mode
//parameter_focus_status
//parameter_video_stabilisation
//parameter_field_of_view
//parameter_high_dynamic_range
//parameter_dynamic_range_compression
//parameter_antishake
//parameter_camera_burst_capture
//parameter_shutter_speed
//parameter_video_denoise
//parameter_analog_gain
//parameter_digital_gain

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace driver {

VideoDriverCaptureProp::VideoDriverCaptureProp (const Acessor& _ph) :
  type_resize_ (videos::generics::convert::TypeSrc2Dst::src_int_dst),
  type_capture_ (TypeCatchRgn::desktop),
  capture_fps_ (0),
  width_ (320),
  height_ (240),
  px_format_ (::libs::helpers::uids::minor::rgb24),
  count_preload_frame_ (1),
  mem_frames_cycle_ (0),
  delay_load_image_ (1000),
  mirror_x_ (false),
  mirror_y_ (false),
  rotation_ (0),
  focus_ (FocusType::auto_generic)
{
  property_name_ = gen_get_type_text_id ();

  return;
}


VideoDriverCaptureProp::~VideoDriverCaptureProp ()
{}


::libs::events::IEvent::ptr
VideoDriverCaptureProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<VideoDriverCaptureProp> (this, _deep);
}


void
VideoDriverCaptureProp::load_int (const base_functs::xml::itn& _prop)
{
  ::libs::ievents::Event::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");
      int                 _ph_int     = 0;

      if (::libs::icore::xml::helpers::load<int> (_param, "type_resize", _ph_int))
        {
          type_resize_ = static_cast<videos::generics::convert::TypeSrc2Dst> (_ph_int);
        }

      if (::libs::icore::xml::helpers::load<int> (_param, "type_capture", _ph_int))
        {
          type_capture_ = static_cast<TypeCatchRgn> (_ph_int);
        }

      if (std::string ("px_format") == _name_param.as_string ())
        {
          px_format_ = boost::uuids::string_generator () (_val_param.as_string ());

          if (::libs::helpers::uids::minor::rgb24 != px_format_ && ::libs::helpers::uids::minor::yuy2 != px_format_)
            {
              XULOG_WARNING ("try use unsupported pixel format, " << ::libs::helpers::uids::helpers::get_readable_name (px_format_));
              px_format_ = ::libs::helpers::uids::minor::rgb24;
            }
        }

      ::libs::icore::xml::helpers::load<unsigned int> (_param, "capture_fps", capture_fps_);
      ::libs::icore::xml::helpers::load<int> (_param, "width", width_);
      ::libs::icore::xml::helpers::load<int> (_param, "height", height_);
      ::libs::icore::xml::helpers::load<unsigned int> (_param, "preload_frame", count_preload_frame_);
      ::libs::icore::xml::helpers::load<unsigned int> (_param, "mem_frames_cycle", mem_frames_cycle_);
      ::libs::icore::xml::helpers::load<int> (_param, "delay_load_image", delay_load_image_);
      ::libs::icore::xml::helpers::load<bool> (_param, "mirror_x", mirror_x_);
      ::libs::icore::xml::helpers::load<bool> (_param, "mirror_y", mirror_y_);
      ::libs::icore::xml::helpers::load<int> (_param, "rotation", rotation_);

      ::libs::icore::xml::helpers::load (_param, "focus", [this](const std::string& _val) {
        focus_ = str2focus (_val);
        return;
      });

      ++_param;
    }

  ::libs::helpers::utils::check_bound<unsigned int> (capture_fps_, 0, 200);
  ::libs::helpers::utils::check_bound<int> (width_, 160, 8 * 1024);
  ::libs::helpers::utils::check_bound<int> (height_, 120, 8 * 1024);
  ::libs::helpers::utils::check_bound<unsigned int> (count_preload_frame_, 0, 8);
  ::libs::helpers::utils::check_bound<int> (delay_load_image_, 0, 60 * 1000);
  ::libs::helpers::utils::check_bound<unsigned int> (mem_frames_cycle_, 0, 24);
  ::libs::helpers::utils::check_bound<int> (rotation_, -360, 360);

  self_correct ();
  return;
}


void
VideoDriverCaptureProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoDriverCaptureProp);
  super::copy_int (_src);
  px_format_           = _dsrc->px_format_;
  type_resize_         = _dsrc->type_resize_;
  type_capture_        = _dsrc->type_capture_;
  width_               = _dsrc->width_;
  height_              = _dsrc->height_;
  count_preload_frame_ = _dsrc->count_preload_frame_;
  mem_frames_cycle_    = _dsrc->mem_frames_cycle_;
  delay_load_image_    = _dsrc->delay_load_image_;
  mirror_x_            = _dsrc->mirror_x_;
  mirror_y_            = _dsrc->mirror_y_;
  rotation_            = _dsrc->rotation_;
  focus_               = _dsrc->focus_;
  return;
}


template <class Archive>
void
VideoDriverCaptureProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (px_format_);
  ar& BOOST_SERIALIZATION_NVP (type_resize_);
  ar& BOOST_SERIALIZATION_NVP (type_capture_);
  ar& BOOST_SERIALIZATION_NVP (width_);
  ar& BOOST_SERIALIZATION_NVP (height_);
  ar& BOOST_SERIALIZATION_NVP (count_preload_frame_);
  ar& BOOST_SERIALIZATION_NVP (mem_frames_cycle_);
  ar& BOOST_SERIALIZATION_NVP (delay_load_image_);
  ar& BOOST_SERIALIZATION_NVP (mirror_x_);
  ar& BOOST_SERIALIZATION_NVP (mirror_y_);
  ar& BOOST_SERIALIZATION_NVP (rotation_);
  ar& BOOST_SERIALIZATION_NVP (focus_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::driver

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::driver::VideoDriverCaptureProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::driver::VideoDriverCaptureProp);
