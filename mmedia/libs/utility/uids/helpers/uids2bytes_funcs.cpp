/**
\file       uids2bytes_funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
\brief      Функции для получения количества байт и размерности от формата данных
*/
#include "../../utility-lib-includes_int.hpp"
#include "uids2bytes_funcs.hpp"

namespace libs::utility::uids::helpers
{
auto
idval2fourcc (const libs::utility::uids::minor::id_val& par) -> std::uint32_t
{
  // UNV12NV12 (0x3231564E)1 Plane of Y → 1 Interleaved Plane of U followed by
  static const boost::unordered_flat_map< libs::utility::uids::minor::id_val, const std::uint32_t > ids2fourccs = {
    { libs::utility::uids::minor::id_val::mjpg, consts::fourcc::mjpg },
    { libs::utility::uids::minor::id_val::rgb32, consts::fourcc::RAW },
    { libs::utility::uids::minor::id_val::rgb24, consts::fourcc::RAW },
    { libs::utility::uids::minor::id_val::y8, consts::fourcc::Y8 },
    { libs::utility::uids::minor::id_val::i420, consts::fourcc::I420 },
    { libs::utility::uids::minor::id_val::yuy2, consts::fourcc::YUY2 },
    { libs::utility::uids::minor::id_val::iyuv, consts::fourcc::VYUY },
    { libs::utility::uids::minor::id_val::yuyv, consts::fourcc::YUYV },
    { libs::utility::uids::minor::id_val::nv21, consts::fourcc::NV21 },
    { libs::utility::uids::minor::id_val::y16, consts::fourcc::Y16 },
    //{ libs::utility::uids::minor::id_val::ycb, consts::fourcc::YVYU },
    //{ libs::utility::uids::minor::id_val::yvyu, consts::fourcc::YVYU },
    { libs::utility::uids::minor::id_val::device_specific, consts::fourcc::RAW }
  };

  auto finger = ids2fourccs.find (par);
  if (ids2fourccs.end () == finger)
  {
    U3_XLOG_WARN ("idval2fourcc:: id_val not found, default value for" + VTOLOG (U3_CAST_UINT32_FORCE (par)) + " is consts::fourcc::YUY2");
    return consts::fourcc::YUY2;
  }
  return finger->second;
}


auto
fourcc2idval (std::uint32_t par) -> libs::utility::uids::minor::id_val
{
  static const boost::unordered_flat_map< std::uint32_t, const libs::utility::uids::minor::id_val > fourccs2ids = {
    { consts::fourcc::mjpg, libs::utility::uids::minor::id_val::mjpg },
    { consts::fourcc::RAW, libs::utility::uids::minor::id_val::rgb32 },
    { consts::fourcc::Y8, libs::utility::uids::minor::id_val::y8 },
    { consts::fourcc::I420, libs::utility::uids::minor::id_val::i420 },
    { consts::fourcc::YUY2, libs::utility::uids::minor::id_val::yuy2 },
    { consts::fourcc::VYUY, libs::utility::uids::minor::id_val::iyuv },
    { consts::fourcc::YUYV, libs::utility::uids::minor::id_val::yuyv }
  };

  auto find = fourccs2ids.find (par);
  if (fourccs2ids.end () == find)
  {
    U3_XLOG_WARN ("fourccs2ids: fourcc not found, default value for " + VTOLOG (par));
    return libs::utility::uids::minor::id_val::unknown;
  }
  return find->second;
}


auto
fourcc2guid (std::uint32_t par) -> const libs::utility::utils::cuuid&
{
  return libs::utility::uids::minor::get (fourcc2idval (par));
}


auto
get_count_bytes_from_format (const libs::utility::uids::minor::id_val& format) -> std::uint32_t
{
  const static boost::unordered_flat_map< libs::utility::uids::minor::id_val, std::uint32_t > vals = {
    { minor::id_val::device_specific, 4 },
    { minor::id_val::rgb32, 4 },
    { minor::id_val::rgb24, 3 },
    { minor::id_val::yuy2, 2 },
    { minor::id_val::ycb, 2 },
    { minor::id_val::yuyv, 2 },
    { minor::id_val::yuyv, 2 },
    { minor::id_val::uyvy, 2 },
    { minor::id_val::iyuv, 2 },
    { minor::id_val::yv12, 2 },
    { minor::id_val::y16, 2 },
    { minor::id_val::rgb555, 2 },
    { minor::id_val::rgb565, 2 },
    { minor::id_val::rgb8, 1 },
    { minor::id_val::y8, 1 },
    { minor::id_val::nv21, 1 },
    { minor::id_val::i420, 1 }
  };

  auto finger = vals.find (format);
  if (vals.end () == finger)
  {
    U3_XLOG_WARN ("get_count_bytes_from_format: unknown id_val format" + TOLOG (to_string (format)));
    // по умолчанию определяем максимальное количество байт на пиксель (т.е. std::int16_t RGBA = 4x2=8 байт)
    return 8;
  }
  return finger->second;
}


auto
get_count_bytes_from_format (const ::libs::utility::utils::cuuid& par) -> std::uint32_t
{
  const auto format = libs::utility::uids::minor::get (par);
  return get_count_bytes_from_format (format);
}


auto
get_hkoeff_from_format (const libs::utility::uids::minor::id_val& format) -> std::uint32_t
{
  if (minor::id_val::nv21 == format || minor::id_val::i420 == format)
  {
    return 2;
  }
  if (format == minor::id_val::yuy2 ||
      format == minor::id_val::yuyv ||
      format == minor::id_val::yuyv ||
      format == minor::id_val::uyvy ||
      format == minor::id_val::ycb ||
      format == minor::id_val::iyuv ||
      format == minor::id_val::yv12 ||
      format == minor::id_val::y16 ||
      format == minor::id_val::rgb555 ||
      format == minor::id_val::rgb565 ||
      format == minor::id_val::rgb24 ||
      format == minor::id_val::rgb32 ||
      format == minor::id_val::rgb8 ||
      format == minor::id_val::y8)
  {
    return 1;
  }
  if (minor::id_val::unknown == format)
  {
    return 1;
  }
  if (format == minor::id_val::device_specific)
  {
    return 1;
  }
  U3_XLOG_WARN ("get_hkoeff_from_format: unacceptable guid format name");
  return 1;
}


auto
get_hkoeff_from_format (const ::libs::utility::utils::cuuid& par) -> std::uint32_t
{
  const auto format = libs::utility::uids::minor::get (par);
  return get_hkoeff_from_format (format);
}


auto
get_readable_name (const libs::utility::uids::minor::id_val& format) -> const std::string&
{
  static const boost::unordered_flat_map< minor::id_val, const std::string > known_ids2names = {
    { minor::id_val::cat_video_device, "cat_video_device" },
    { minor::id_val::audio_devices, "audio_devices" },
    { minor::id_val::audio_compressors, "audio_compressors" },
    { minor::id_val::audio_renderers, "audio_renderers" },
    { minor::id_val::legacy_am_filters, "legacy_am_filters" },
    { minor::id_val::midi_renders, "midi_renders" },
    { minor::id_val::video_compressors, "video_compressors" },
    { minor::id_val::ctrl_driver_dshow, "ctrl_driver_dshow" },
    { minor::id_val::idata_source, "idata_source" },
    { minor::id_val::video, "video" },
    { minor::id_val::audio, "audio" },
    { minor::id_val::unknown, "unknown/FF/" },
    { minor::id_val::device_specific, "device_specific" },
    { minor::id_val::compressed, "compressed" },
    { minor::id_val::y8, "Y8" },
    { minor::id_val::y16, "Y16" },
    { minor::id_val::i420, "I420" },
    { minor::id_val::yuy2, "YUY2" },
    { minor::id_val::ycb, "YCB" },
    { minor::id_val::uyvy, "UYVY" },
    { minor::id_val::rgb24, "RGB24" },
    { minor::id_val::rgb555, "RGB555" },
    { minor::id_val::rgb565, "RGB565" },
    { minor::id_val::rgb8, "RGB8" },
    { minor::id_val::rgb32, "RGB32" },
    { minor::id_val::iyuv, "IYUV" },
    { minor::id_val::yv12, "YV12" },
    { minor::id_val::yvu9, "YVU9" },
    { minor::id_val::yuyv, "YUYV" },
    { minor::id_val::y211, "Y211" },
    { minor::id_val::if09, "If09" },
    { minor::id_val::nv21, "NV21" },
    { minor::id_val::mjpg, "MJPG" },
    { minor::id_val::x264, "X264" },
    { minor::id_val::x265, "X265" },
    { minor::id_val::av1, "AV1" },
    { minor::id_val::mjpeg, "MJPEG" },
    { minor::id_val::mjpg1, "MJPG1" },
    { minor::id_val::mjpg2, "MJPG2" },
    { minor::id_val::mjpg4, "MJPG4" },
    { minor::id_val::test, "test coder" }
  };

  auto finger = known_ids2names.find (format);
  if (finger == known_ids2names.end ())
  {
    finger = known_ids2names.find (minor::id_val::unknown);
  }
  return finger->second;
}


auto
get_readable_name (const ::libs::utility::utils::cuuid& par) -> const std::string&
{
  const auto format = libs::utility::uids::minor::get (par);
  return get_readable_name (format);
}


auto
is_raw_format (const libs::utility::uids::minor::id_val& format) -> bool
{
  static const boost::unordered_flat_map< minor::id_val, const bool > raw_guids = {
    { minor::id_val::y8, true },
    { minor::id_val::y16, true },
    { minor::id_val::i420, true },
    { minor::id_val::yuy2, true },
    { minor::id_val::ycb, true },
    { minor::id_val::uyvy, true },
    { minor::id_val::rgb24, true },
    { minor::id_val::rgb555, true },
    { minor::id_val::rgb565, true },
    { minor::id_val::rgb8, true },
    { minor::id_val::rgb32, true },
    { minor::id_val::iyuv, true },
    { minor::id_val::yv12, true },
    { minor::id_val::yvu9, true },
    { minor::id_val::yuyv, true },
    { minor::id_val::y211, true },
    { minor::id_val::if09, true },
    { minor::id_val::nv21, true },
    { minor::id_val::device_specific, true },

    { minor::id_val::compressed, false },
    { minor::id_val::mjpg, false },
    { minor::id_val::x264, false },
    { minor::id_val::x265, false },
    { minor::id_val::av1, false }
  };

  auto find = raw_guids.find (format);
  if (raw_guids.end () == find)
  {
    U3_XLOG_WARN ("try check raw unknown format name");
    return false;
  }

  return find->second;
}


auto
is_raw_format (const ::libs::utility::utils::cuuid& par) -> bool
{
  const auto format = minor::get (par);
  return is_raw_format (format);
}
}   // namespace libs::utility::uids::helpers
