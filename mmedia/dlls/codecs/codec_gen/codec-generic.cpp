/**
\file       codec-generic.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_codec_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "codec-gen-includes_int.hpp"
#include "codec-generic.hpp"

namespace dlls::codecs::codec_gen
{
CodecGeneric::CodecGeneric () :
  counter_frames_ (0),
  simd_ (syn::CpuExts::usual),
  transinfo_ (nullptr),
  id_node_graph_ (nullptr)
{
}


CodecGeneric::~CodecGeneric ()
{
}


void
CodecGeneric::init (const InfoGenCodec& info)
{
  init_int (info);
}


void
CodecGeneric::code (
  const ::libs::bufs::Bufs*         src,
  ::libs::bufs::Bufs*               dst,
  syn::TransformInfo::tevents_type* events)
{
  if (code_int (src, dst, events))
  {
    ++counter_frames_;
  }
}


void
CodecGeneric::decode (
  const ::libs::bufs::Bufs*         src,
  ::libs::bufs::Bufs*               dst,
  syn::TransformInfo::tevents_type* events)
{
  if (decode_int (src, dst, events))
  {
    ++counter_frames_;
  }
}


void
CodecGeneric::set_codec_info (const syn::VideoCodecProp* info)
{
  if (!info)
  {
    return;
  }
  set_codec_info_int (info);
}


void
CodecGeneric::get_codec_info (syn::VideoCodecProp* info)
{
  if (!info)
  {
    return;
  }
  get_codec_info_int (info);
}


void
CodecGeneric::set_transform_info (
  const syn::NodeID*  id_node,
  syn::TransformInfo* tranform_info)
{
  transinfo_     = tranform_info;
  id_node_graph_ = id_node;
}


void
CodecGeneric::set_cpu (syn::CpuExts optim)
{
  set_cpu_int (optim);
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
}
}   // namespace dlls::codecs::codec_gen
