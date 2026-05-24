#pragma once
/**
\file       minor.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::uids::minor
{
enum class id_val : std::uint32_t
{
  device_specific = 0,
  compressed,
  y8,
  y16,
  i420,
  yuy2,
  ycb,
  uyvy,
  rgb24,
  rgb555,
  rgb565,
  rgb8,
  rgb32,
  iyuv,
  yv12,
  yvu9,
  yuyv,
  y211,
  if09,
  nv21,
  mjpg,
  video,
  audio,
  ctrl_driver_dshow,
  idata_source,
  any_codec,
  mjpeg,
  mjpg1,
  mjpg2,
  mjpg4,
  x264,
  x265,
  test,
  vp7,
  vp9,
  mp3,
  aac,
  ogg,
  ilbc,
  g723_1,
  av1,
  cat_video_device,
  audio_devices,
  audio_compressors,
  audio_renderers,
  legacy_am_filters,
  midi_renders,
  video_compressors,
  unknown = 0xFFFFFFFF
};

const ::libs::helpers::utils::cuuid& get (const id_val& val);
id_val                               get (const ::libs::helpers::utils::cuuid&);

inline id_val
from_raw_value (std::uint32_t val)
{
  return U3_CAST_STATIC< id_val > (val);
}
}   // namespace libs::helpers::uids::minor
