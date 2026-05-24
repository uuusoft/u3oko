/**
\file       video-codec-flat-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-codec-flat-prop.hpp"

namespace libs::ievents::props::videos::generic::codec
{
VideoCodecFlatProp::VideoCodecFlatProp (
  const libs::helpers::uids::minor::id_val& format,
  const CodecModes&                         type,
  std::uint32_t                             quality,
  float                                     max_percent_pframe,
  std::uint32_t                             max_period_kframe,
  float                                     percent_block,
  bool                                      nocolor) :

  size_ (sizeof (VideoCodecFlatProp)),
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

  ::libs::helpers::utils::check_float (&max_percent_pframe_);
  ::libs::helpers::utils::check_float (&percent_block_);

  ::libs::helpers::utils::check_bound (quality_, 0u, 100u);
  ::libs::helpers::utils::check_bound (max_percent_pframe_, 1.0f, 10.0f);
  ::libs::helpers::utils::check_bound (max_period_kframe_, 1u, 10 * 1024u);
  ::libs::helpers::utils::check_bound (percent_block_, 0.0f, 100.0f);
}


void
VideoCodecFlatProp::reset ()
{
  size_ = sizeof (VideoCodecFlatProp);

  format_             = libs::helpers::uids::minor::id_val::unknown;
  quality_            = 50;
  max_percent_pframe_ = 8.0f;
  max_period_kframe_  = 500;
  percent_block_      = 8.0f;
  type_               = CodecModes::coder;
  nocolor_            = false;
}


const VideoCodecFlatProp&
VideoCodecFlatProp::operator= (const VideoCodecFlatProp& lhs)
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


std::string
to_string (const VideoCodecFlatProp& info)
{
  std::stringstream str;
  return str.str ();
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const VideoCodecFlatProp& src)
{
  // EAI-JSON-TEST-86
  jv = {
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


VideoCodecFlatProp
tag_invoke (::boost::json::value_to_tag< VideoCodecFlatProp >, const ::boost::json::value& jv)
{
  VideoCodecFlatProp ret;

  ret.size_               = ::libs::helpers::json::get_uint32 (jv.at ("size"));
  ret.max_percent_pframe_ = ::libs::helpers::json::get_float (jv.at ("max_percent_pframe"));
  ret.max_period_kframe_  = ::libs::helpers::json::get_uint32 (jv.at ("max_period_kframe"));
  ret.percent_block_      = ::libs::helpers::json::get_float (jv.at ("percent_block"));
  ret.type_               = U3_CAST_STATIC< libs::ievents::props::videos::generic::codec::CodecModes > (::libs::helpers::json::get_uint32 (jv.at ("codec_mode")));
  ret.format_             = U3_CAST_STATIC< libs::helpers::uids::minor::id_val > (::libs::helpers::json::get_uint32 (jv.at ("format")));
  ret.quality_            = ::libs::helpers::json::get_uint32 (jv.at ("quality"));
  ret.nocolor_            = ::libs::helpers::json::get_bool (jv.at ("nocolor"));
  return ret;
}


std::uint32_t
to_bitrate_x264 (const VideoCodecFlatProp& info, std::uint32_t width, std::uint32_t height)
{
  // see openx264 ecoder_ext.cpp:3909 (pParam->iVideoWidth * pParam->iVideoHeight * 3) >> 2
  return (width * height * 3 * 8 / 2) * (info.quality_ + 1) / 101.0f;
}
}   // namespace libs::ievents::props::videos::generic::codec
