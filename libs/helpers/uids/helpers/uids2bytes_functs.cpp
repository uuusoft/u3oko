//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       uids2bytes_functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Функции для получения количества байт и размерности от формата данных.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "uids2bytes_functs.hpp"

namespace libs { namespace helpers { namespace uids { namespace helpers {

int
get_count_bytes_from_format (const ::libs::helpers::utils::cuuid& _format)
{
  if (_format == minor::rgb32)
    {
      return 4;
    }

  if (_format == minor::rgb24)
    {
      return 3;
    }

  if ((_format == minor::yuy2) || (_format == minor::ycb) || (_format == minor::yuyv) || (_format == minor::yuyv) || (_format == minor::uyvy))
    {
      return 2;
    }

  if ((minor::i420 == _format) || (minor::iyuv == _format) || (minor::yv12 == _format) || (minor::y16 == _format))
    {
      return 2;
    }

  if ((_format == minor::rgb555) || (_format == minor::rgb565))
    {
      return 2;
    }

  if ((_format == minor::rgb8) || (_format == minor::y8) || (minor::nv21 == _format))
    {
      return 1;
    }

  XULOG_WARNING ("get_count_bytes_from_format: unacceptable guid format, " << get_readable_name (_format));
  //  по умолчанию определяем максимальное количество байт на пиксель (т.е. short RGBA = 4x2=8).
  return 8;
}


int
get_hkoeff_from_format (const ::libs::helpers::utils::cuuid& _format)
{
  if (minor::nv21 == _format)
    {
      return 2;
    }

  if ((_format == minor::yuy2) || (_format == minor::yuyv) || (_format == minor::yuyv) || (_format == minor::uyvy) || (_format == minor::ycb))
    {
      return 1;
    }

  if ((minor::i420 == _format) || (minor::iyuv == _format) || (minor::yv12 == _format) || (minor::y16 == _format))
    {
      return 1;
    }

  if ((_format == minor::rgb555) || (_format == minor::rgb565) || (_format == minor::rgb24) || (_format == minor::rgb32))
    {
      return 1;
    }

  if ((_format == minor::rgb8) || (_format == minor::y8))
    {
      return 1;
    }

  if (_format.empty ())
    {
      return 1;
    }

  XULOG_WARNING ("get_hkoeff_from_format: unacceptable guid format, " << get_readable_name (_format));
  return 1;
}


std::string
get_readable_name (const utils::cuuid& _format)
{
  static const std::pair<utils::cuuid, std::string> unknow_guids[] = {
    { cat::cat_video_device, "cat_video_device" },
    { cat::audio_devices, "audio_devices" },
    { cat::audio_compressors, "audio_compressors" },
    { cat::audio_renderers, "audio_renderers" },
    { cat::legacy_am_filters, "legacy_am_filters" },
    { cat::midi_renders, "midi_renders" },
    { cat::video_compressors, "video_compressors" },

    { interf::ctrl_driver_dshow, "ctrl_driver_dshow" },
    { interf::idata_source, "idata_source" },

    { major::video, "video" },
    { major::audio, "audio" },

    { minor::unknow, "unknown [null]" },
    { minor::device_specific, "device_specific" },
    { minor::y8, "y8" },
    { minor::y16, "y16" },
    { minor::i420, "i420" },
    { minor::yuy2, "yuy2" },
    { minor::ycb, "ycb" },
    { minor::uyvy, "uyvy" },
    { minor::rgb24, "rgb24" },
    { minor::rgb555, "rgb555" },
    { minor::rgb565, "rgb565" },
    { minor::rgb8, "rgb8" },
    { minor::rgb32, "rgb32" },
    { minor::iyuv, "iyuv" },
    { minor::yv12, "yv12" },
    { minor::yvu9, "yvu9" },
    { minor::yuyv, "yuyv" },
    { minor::y211, "y211" },
    { minor::if09, "if09" },
    { minor::nv21, "nv21" },
    { minor::mjpg, "mjpg" },
    { minor::x264, "x264" },

    { codecs::mjpeg, "mjpeg coder" },
    { codecs::mjpg1, "mjpg1 coder" },
    { codecs::mjpg2, "mjpg2 coder" },
    { codecs::mjpg4, "mjpg4 coder" },
    { codecs::x264, "x264 coder" },
    { codecs::x265, "x265 coder" },
    { codecs::test, "test coder" }
  };

  for (const auto& _guid : unknow_guids)
    {
      if (_guid.first == _format)
        {
          return _guid.second;
        }
    }
  return "#unknown guid: " + _format.name ();
}


bool
is_raw_format (const utils::cuuid& _format)
{
  static const std::unordered_map<utils::cuuid, bool> raw_guids = {
    { minor::y8, true },
    { minor::y16, true },
    { minor::i420, true },
    { minor::yuy2, true },
    { minor::ycb, true },
    { minor::uyvy, true },
    { minor::rgb24, true },
    { minor::rgb555, true },
    { minor::rgb565, true },
    { minor::rgb8, true },
    { minor::rgb32, true },
    { minor::iyuv, true },
    { minor::yv12, true },
    { minor::yvu9, true },
    { minor::yuyv, true },
    { minor::y211, true },
    { minor::if09, true },
    { minor::nv21, true },

    { minor::mjpg, false },
    { minor::x264, false }
  };

  auto _find = raw_guids.find (_format);
  if (raw_guids.end () == _find)
    {
      XULOG_WARNING ("try check raw unknown format, " << get_readable_name (_format));
      return false;
    }

  return _find->second;
}

}}}}      // namespace libs::helpers::uids::helpers
