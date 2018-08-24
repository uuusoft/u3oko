//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       dump-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2018
\copyright  www.uuusoft.com
\project    uuu_dshow_vgen
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "includes_int.hpp"
#include "dump-functs.hpp"

namespace libs { namespace helpers { namespace dshow {

#if defined(UUU_OS_WIN32_DESKTOP)

std::string
to_str_dword (const DWORD _val)
{
  return to_str (UUU_ICAST_CHAR (_val & 0xFF)) + to_str (UUU_ICAST_CHAR (_val >> 8 & 0xFF)) + to_str (UUU_ICAST_CHAR (_val >> 16 & 0xFF)) + to_str (UUU_ICAST_CHAR (_val >> 24 & 0xFF));
}

std::string
to_str_rect (const RECT& _rect)
{
  std::string _ret;
  _ret += "[" + to_str (_rect.left) + "." + to_str (_rect.top) + "x" + to_str (_rect.right) + "." + to_str (_rect.bottom) + "]";
  return _ret;
}

std::string
to_str_bi_compression (const DWORD _val)
{
  switch (_val)
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

  return to_str_dword (_val);
}


void
dump (const BITMAPINFOHEADER& _info)
{
  XULOG_INFO ("dump BITMAPINFOHEADER:");
  XULOG_INFO ("   biBitCount=" << _info.biBitCount << ", biCompression=" << to_str_bi_compression (_info.biCompression) << ", biWidth=" << _info.biWidth << ", biHeight=" << _info.biHeight << ", biPlanes=" << _info.biPlanes);
  XULOG_INFO ("   biClrImportant=" << _info.biClrImportant << ", biClrUsed=" << _info.biClrUsed << ", biSize=" << _info.biSize << ", biXPelsPerMeter=" << _info.biXPelsPerMeter << ", biYPelsPerMeter=" << _info.biYPelsPerMeter);
  return;
}


void
dump (const VIDEOINFOHEADER& _info)
{
  XULOG_INFO ("dump VIDEOINFOHEADER:");
  XULOG_INFO ("   AvgTimePerFrame=" << _info.AvgTimePerFrame << ", dwBitErrorRate=" << _info.dwBitErrorRate << ", dwBitRate=" << _info.dwBitRate);
  XULOG_INFO ("   rcSource=" << to_str_rect (_info.rcSource) << ", rcTarget=" << to_str_rect (_info.rcTarget));
  dump (_info.bmiHeader);
  return;
}


void
dump (const VIDEOINFOHEADER2& _info)
{
  XULOG_INFO ("dump VIDEOINFOHEADER2:");
  dump (_info.bmiHeader);
  //_info.
  return;
}


void
dump (const AM_MEDIA_TYPE* _minfo)
{
  XULOG_INFO ("dump AM_MEDIA_TYPE:");
  XULOG_INFO ("   formattype=" << utils::cuuid (_minfo->formattype).name () << ", majortype=" << utils::cuuid (_minfo->majortype).name () << ", subtype=" << utils::cuuid (_minfo->subtype).name ());
  XULOG_INFO ("   lSampleSize=" << _minfo->lSampleSize << ", bFixedSizeSamples=" << _minfo->bFixedSizeSamples << ", bTemporalCompression=" << _minfo->bTemporalCompression);

  if (FORMAT_VideoInfo == _minfo->formattype)
    {
      UASSERT (_minfo->pbFormat);
      UASSERT (_minfo->cbFormat >= sizeof (FORMAT_VideoInfo))
      VIDEOINFOHEADER* _info = UUU_MEM_CAST<VIDEOINFOHEADER*> (_minfo->pbFormat);
      dump (*_info);
      return;
    }

  if (FORMAT_VideoInfo2 == _minfo->formattype)
    {
      UASSERT (_minfo->pbFormat);
      UASSERT (_minfo->cbFormat >= sizeof (FORMAT_VideoInfo2));
      VIDEOINFOHEADER2* _info = UUU_MEM_CAST<VIDEOINFOHEADER2*> (_minfo->pbFormat);
      dump (*_info);
      return;
    }

  XULOG_WARNING ("    unknow guid formattype AM_MEDIA_TYPE");
  return;
}

#if 0
void
dump (const IPinPtr& _ipin)
{
  XULOG_INFO ("IPin->");
  interf::IAMStreamConfigPtr _iam_stream;
  HRESULT                    _hr = _ipin->QueryInterface (IID_IAMStreamConfig, UUU_CONVERT2VOID (&_iam_stream.update ()));

  if (FAILED (_hr) || !*_iam_stream)
    {
      XULOG_ERROR ("failed query IID_IAMStreamConfig from pin");
      return;
    }

  PIN_INFO _pin_info = { nullptr, PINDIR_INPUT };
  memset (&_pin_info, 0, sizeof (_pin_info));
  if (SUCCEEDED (_ipin->QueryPinInfo (&_pin_info)))
    {
      //XULOG_INFO (_pin_info.achName << ", direction=" << _pin_info.dir);
      XULOG_INFO (", direction=" << _pin_info.dir);
    }

  int           _capcount = 0;
  int           _capsize  = 0;
  unsigned char _raw_buff[(sizeof (VIDEO_STREAM_CONFIG_CAPS) + sizeof (AUDIO_STREAM_CONFIG_CAPS)) * 2];

  //  check final format
  _hr = (*_iam_stream)->GetNumberOfCapabilities (&_capcount, &_capsize);

  if ((FAILED (_hr)))
    {
      XULOG_ERROR ("failed get number capabilities");
      return;
    }

  if ((0 >= _capcount) || (_capsize > sizeof (_raw_buff)))
    {
      XULOG_ERROR ("invalid params");
      return;
    }

  XULOG_INFO ("capcount=" << _capcount << ", capsize=" << _capsize);

  for (int _indx = 0; _indx < _capcount; ++_indx)
    {
      XULOG_INFO ("indx=" << _indx);
      AM_MEDIA_TYPE* _minfo = nullptr;

      _hr = (*_iam_stream)->GetStreamCaps (_indx, &_minfo, _raw_buff);

      if (FAILED (_hr))
        {
          XULOG_ERROR ("failed get caps, indx=" << _indx << ", 0x" << std::hex << _hr);
          continue;
        }

      dump (_minfo);
    }
  return;
}
#endif
#endif

}}}      // namespace libs::helpers::dshow
