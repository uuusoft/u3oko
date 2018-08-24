//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       codec-generic.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_codec_gen
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "codec-generic.hpp"

namespace dlls { namespace codecs { namespace codec_gen {

CodecGeneric::CodecGeneric ()
{
  simd_ = TypeExtCpu::usual;
}


CodecGeneric::~CodecGeneric ()
{}


void
CodecGeneric::init (const InfoGenCodec& _info)
{
  init_int (_info);
  return;
}


void
CodecGeneric::code (const Buffs* _src, Buffs* _dst, events_type* _events)
{
  code_int (_src, _dst, _events);
  return;
}


void
CodecGeneric::decode (const Buffs* _src, Buffs* _dst, events_type* _events)
{
  decode_int (_src, _dst, _events);
  return;
}


void
CodecGeneric::set_codec_info (const VideoCodecProp* _info)
{
  if (!_info)
    {
      return;
    }
  set_codec_info_int (_info);
  return;
}


void
CodecGeneric::get_codec_info (VideoCodecProp* _info)
{
  if (!_info)
    {
      return;
    }
  get_codec_info_int (_info);
  return;
}


void
CodecGeneric::set_cpu (TypeExtCpu _optim)
{
  set_cpu_int (_optim);
  return;
}


const StatisticInfo&
CodecGeneric::get_statistic_info () const
{
  return get_statistic_info_int ();
}


void
CodecGeneric::reset_statistic_info ()
{
  reset_statistic_info_int ();
  return;
}

}}}      // namespace dlls::codecs::codec_gen
