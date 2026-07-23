/**
\file       video-codec-flat-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "video-codec-flat-prop.hpp"

namespace libs::events_base::props::videos::generic::codec
{
VideoCodecFlatProp::VideoCodecFlatProp (
  const libs::utility::uids::minor::id_val& format,
  const CodecModes&                         type,
  std::uint32_t                             quality,
  float                                     max_percent_pframe,
  std::uint32_t                             max_period_kframe,
  float                                     percent_block,
  bool                                      nocolor) :
  format_ (format),
  type_ (type),
  quality_ (quality),
  max_percent_pframe_ (max_percent_pframe),
  max_period_kframe_ (max_period_kframe),
  percent_block_ (percent_block),
  nocolor_ (nocolor)
{
}


VideoCodecFlatProp::VideoCodecFlatProp (const VideoCodecFlatProp& op)
{
  (*this) = op;
}


void
VideoCodecFlatProp::correct ()
{
  size_ = sizeof (VideoCodecFlatProp);

  ::libs::utility::utils::check_float (&max_percent_pframe_);
  ::libs::utility::utils::check_float (&percent_block_);

  ::libs::utility::utils::check_bound (quality_, 0U, 100U);
  ::libs::utility::utils::check_bound (max_percent_pframe_, 1.0F, 10.0F);
  ::libs::utility::utils::check_bound (max_period_kframe_, 1U, 10 * 1024U);
  ::libs::utility::utils::check_bound (percent_block_, 0.0F, 100.0F);
}


void
VideoCodecFlatProp::reset ()
{
  size_ = sizeof (VideoCodecFlatProp);

  format_             = libs::utility::uids::minor::id_val::unknown;
  quality_            = 50;
  max_percent_pframe_ = 8.0F;
  max_period_kframe_  = 500;
  percent_block_      = 8.0F;
  type_               = CodecModes::coder;
  nocolor_            = false;
}


auto
VideoCodecFlatProp::operator= (const VideoCodecFlatProp& lhs) -> const VideoCodecFlatProp&
{
  size_               = sizeof (VideoCodecFlatProp);
  format_             = lhs.format_;
  type_               = lhs.type_;
  quality_            = lhs.quality_;
  max_percent_pframe_ = lhs.max_percent_pframe_;
  max_period_kframe_  = lhs.max_period_kframe_;
  percent_block_      = lhs.percent_block_;
  nocolor_            = lhs.nocolor_;
  return *this;
}


auto
to_string (const VideoCodecFlatProp& info) -> std::string
{
  std::stringstream str;
  return str.str ();
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const VideoCodecFlatProp& src)
{
  jvs = {
    { "size", src.size_ },
    { "format", U3_CAST_UINT32_FORCE (src.format_) },
    { "max_percent_pframe", src.max_percent_pframe_ },
    { "max_period_kframe", src.max_period_kframe_ },
    { "percent_block", src.percent_block_ },
    { "codec_mode", U3_CAST_UINT32_FORCE (src.type_) },
    { "quality", src.quality_ },
    { "nocolor", src.nocolor_ }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< VideoCodecFlatProp >, const ::boost::json::value& jvs) -> VideoCodecFlatProp
{
  VideoCodecFlatProp ret;

  ret.size_               = ::libs::utility::json::get_uint32 (jvs.at ("size"));
  ret.max_percent_pframe_ = ::libs::utility::json::get_float (jvs.at ("max_percent_pframe"));
  ret.max_period_kframe_  = ::libs::utility::json::get_uint32 (jvs.at ("max_period_kframe"));
  ret.percent_block_      = ::libs::utility::json::get_float (jvs.at ("percent_block"));
  ret.type_               = ::libs::utility::casts::static_cast_helper< libs::events_base::props::videos::generic::codec::CodecModes > (::libs::utility::json::get_uint32 (jvs.at ("codec_mode")));
  ret.format_             = ::libs::utility::casts::static_cast_helper< libs::utility::uids::minor::id_val > (::libs::utility::json::get_uint32 (jvs.at ("format")));
  ret.quality_            = ::libs::utility::json::get_uint32 (jvs.at ("quality"));
  ret.nocolor_            = ::libs::utility::json::get_bool (jvs.at ("nocolor"));
  return ret;
}


auto
to_bitrate_x264 (const VideoCodecFlatProp& info, std::uint32_t width, std::uint32_t height) -> std::uint32_t
{
  // see openx264 ecoder_ext.cpp:3909 (pParam->iVideoWidth * pParam->iVideoHeight * 3) >> 2
  return (width * height * 3 * 8 / 2) * (info.quality_ + 1) / 101.0F;
}
}   // namespace libs::events_base::props::videos::generic::codec
