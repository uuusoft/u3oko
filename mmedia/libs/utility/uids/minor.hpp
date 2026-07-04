#pragma once
/**
\file       minor.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::utility::uids::minor
{
enum class id_val : std::uint32_t
{
  device_specific   = 0,
  compressed        = 1,
  y8                = 2,
  y16               = 3,
  i420              = 4,
  yuy2              = 5,
  ycb               = 6,
  uyvy              = 7,
  rgb24             = 8,
  rgb555            = 9,
  rgb565            = 10,
  rgb8              = 11,
  rgb32             = 12,
  iyuv              = 13,
  yv12              = 14,
  yvu9              = 15,
  yuyv              = 16,
  y211              = 17,
  if09              = 18,
  nv21              = 19,
  mjpg              = 20,
  video             = 200,
  any_codec         = 201,
  mjpeg             = 202,
  mjpg1             = 203,
  mjpg2             = 204,
  mjpg4             = 205,
  x264              = 206,
  x265              = 207,
  test              = 208,
  vp7               = 209,
  av1               = 210,
  vp9               = 211,
  audio             = 300,
  mp3               = 301,
  aac               = 302,
  ogg               = 303,
  ilbc              = 304,
  g723_1            = 305,
  ctrl_driver_dshow = 400,
  idata_source      = 401,
  cat_video_device  = 1000,
  audio_devices     = 1001,
  audio_compressors = 1002,
  audio_renderers   = 1003,
  legacy_am_filters = 1004,
  midi_renders      = 1005,
  video_compressors = 1006,
  unknown           = 0xFFFFFFFF
};

auto get (const id_val& val) -> const ::libs::utility::utils::cuuid&;
auto get (const ::libs::utility::utils::cuuid&) -> id_val;
auto to_string (const id_val&) -> const std::string&;

inline id_val
from_raw_value (std::uint32_t val)
{
  return ::libs::utility::casts::static_cast_helper< id_val > (val);
}
}   // namespace libs::utility::uids::minor
