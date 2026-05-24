#pragma once
/**
\file       vcodec-x264-syn.hpp
\date       23.08.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_x264
*/

namespace dlls::codecs::vcodec_x264::syn
{
using StatisticInfo   = ::dlls::codecs::codec_gen::StatisticInfo;
using VideoCodecProp  = ::libs::ievents::props::videos::generic::codec::VideoCodecProp;
using IVideoBuf       = ::utils::dbufs::video::IVideoBuf;
using TransformInfo   = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CodecModes      = ::libs::ievents::props::videos::generic::codec::CodecModes;
using AllocBufInfo    = ::utils::dbufs::video::AllocBufInfo;
using HeaderIFrame    = ::dlls::codecs::codec_gen::HeaderIFrame;
using ISystemProperty = ::libs::iproperties::vers::system::ISystemProperty;
}   // namespace dlls::codecs::vcodec_x264::syn
