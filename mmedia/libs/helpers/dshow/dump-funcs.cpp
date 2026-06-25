/**
\file       dump-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2018
\project    u3_dshow_vgen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "includes_int.hpp"
#include "dump-funcs.hpp"

// old shit
#ifdef U3_OS_WIN32_DESKTOP

namespace libs::helpers::dshow
{
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
std::string
to_str_dword (const DWORD val)
{
  return std::to_string (U3_CAST_INT8 (val & 0xFF)) + std::to_string (U3_CAST_INT8 (val >> 8 & 0xFF)) + std::to_string (U3_CAST_INT8 (val >> 16 & 0xFF)) + std::to_string (U3_CAST_INT8 (val >> 24 & 0xFF));
}


std::string
to_str_rect (const RECT& rect)
{
  std::string ret;
  ret += "[" + std::to_string (rect.left) + "." + std::to_string (rect.top) + "x" + std::to_string (rect.right) + "." + std::to_string (rect.bottom) + "]";
  return ret;
}


std::string
to_str_bi_compression (const DWORD val)
{
  switch (val)
  {
  case consts::compression::rgb:
    return "rgb";
  case consts::compression::bitfields:
    return "bitfields";
  case consts::compression::rle8:
    return "rle8";
  case consts::compression::rle4:
    return "rle4";
  case consts::compression::jpeg:
    return "jpeg";
  case consts::compression::png:
    return "png";
  case consts::compression::mjpg:
    return "MJPG";
  case consts::compression::i420:
    return "I420";
  }

  return to_str_dword (val);
}


void
dump (const BITMAPINFOHEADER& info)
{
  U3_XLOG_WARN ("dump BITMAPINFOHEADER:");
  U3_XLOG_WARN (VTOLOG (info.biBitCount) + to_str_bi_compression (info.biCompression) + VTOLOG (info.biWidth) + VTOLOG (info.biHeight) + VTOLOG (info.biPlanes));
  U3_XLOG_WARN (VTOLOG (info.biClrImportant) + VTOLOG (info.biClrUsed) + VTOLOG (info.biSize) + VTOLOG (info.biXPelsPerMeter) + VTOLOG (info.biYPelsPerMeter));
}


void
dump (const VIDEOINFOHEADER& info)
{
  U3_XLOG_WARN ("dump VIDEOINFOHEADER:");
  U3_XLOG_WARN (VTOLOG (info.AvgTimePerFrame) + VTOLOG (info.dwBitErrorRate) + VTOLOG (info.dwBitRate));
  U3_XLOG_WARN ("source rect=" + to_str_rect (info.rcSource) + " target rect=" + to_str_rect (info.rcTarget));
  dump (info.bmiHeader);
}


void
dump (const VIDEOINFOHEADER2& info)
{
  U3_XLOG_WARN ("dump VIDEOINFOHEADER2:");
  dump (info.bmiHeader);
}


void
dump (const AM_MEDIA_TYPE* minfo)
{
  U3_XLOG_WARN ("dump AM_MEDIA_TYPE:");
  U3_XLOG_WARN (::libs::helpers::utils::to_string (utils::cuuid (minfo->formattype)) + " majortype=" + ::libs::helpers::utils::to_string (utils::cuuid (minfo->majortype)) + " subtype=" + ::libs::helpers::utils::to_string (utils::cuuid (minfo->subtype)));
  U3_XLOG_WARN (VTOLOG (minfo->lSampleSize) + VTOLOG (minfo->bFixedSizeSamples) + VTOLOG (minfo->bTemporalCompression));

  if (FORMAT_VideoInfo == minfo->formattype)
  {
    U3_ASSERT (minfo->pbFormat);
    U3_ASSERT (minfo->cbFormat >= sizeof (FORMAT_VideoInfo))
    auto* info = ::libs::helpers::casts::reinterpret_cast_helper< VIDEOINFOHEADER* > (minfo->pbFormat);
    dump (*info);
    return;
  }

  if (FORMAT_VideoInfo2 == minfo->formattype)
  {
    U3_ASSERT (minfo->pbFormat);
    U3_ASSERT (minfo->cbFormat >= sizeof (FORMAT_VideoInfo2));
    auto* info = ::libs::helpers::casts::reinterpret_cast_helper< VIDEOINFOHEADER2* > (minfo->pbFormat);
    dump (*info);
    return;
  }

  U3_XLOG_WARN ("unknow guid formattype AM_MEDIA_TYPE");
}
#  endif
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void
dump (const IPinPtr& ipin)
{
  interf::IAMStreamConfigPtr iam_stream;
  HRESULT                    hr = ipin->QueryInterface (IID_IAMStreamConfig, ::libs::helpers::casts::reinterpret_cast_helper< void** > (&iam_stream.update ()));

  if (FAILED (hr) || !*iam_stream)
  {
    U3_XLOG_ERROR ("query IID_IAMStreamConfig from pin");
    return;
  }

  PIN_INFO pin_info = { nullptr, PINDIR_INPUT };
  memset (&pin_info, 0, sizeof (pin_info));
  if (SUCCEEDED (ipin->QueryPinInfo (&pin_info)))
  {
    //
  }

  int          capcount = 0;
  int          capsize  = 0;
  std::uint8_t raw_buf[(sizeof (VIDEO_STREAM_CONFIG_CAPS) + sizeof (AUDIO_STREAM_CONFIG_CAPS)) * 2];

  //  check final format
  hr = (*iam_stream)->GetNumberOfCapabilities (&capcount, &capsize);

  if ((FAILED (hr)))
  {
    U3_XLOG_ERROR ("get number capabilities");
    return;
  }

  if ((0 >= capcount) || (capsize > sizeof (raw_buf)))
  {
    U3_XLOG_ERROR ("invalid params");
    return;
  }


  for (int indx = 0; indx < capcount; ++indx)
  {
    AM_MEDIA_TYPE* minfo = nullptr;

    hr = (*iam_stream)->GetStreamCaps (indx, &minfo, raw_buf);

    if (FAILED (hr))
    {
      U3_XLOG_ERROR ("get caps, indx=" << indx << ", 0x" << std::hex << hr);
      continue;
    }

    dump (minfo);
  }
}
#  endif
}   // namespace libs::helpers::dshow
#endif
