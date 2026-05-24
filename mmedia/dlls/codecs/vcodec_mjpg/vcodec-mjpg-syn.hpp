#pragma once
/**
\file       vcodec-mjpg-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_mjpg
*/

namespace dlls::codecs::vcodec_mjpg::syn
{
using VideoCodecProp = ::libs::ievents::props::videos::generic::codec::VideoCodecProp;
using TransformInfo  = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using VideoCodecProp = ::libs::ievents::props::videos::generic::codec::VideoCodecProp;
using IVideoBuf      = ::utils::dbufs::video::IVideoBuf;
using StatisticInfo  = ::dlls::codecs::codec_gen::StatisticInfo;
using AllocBufInfo   = ::utils::dbufs::video::AllocBufInfo;
using HeaderIFrame   = ::dlls::codecs::codec_gen::HeaderIFrame;
}   // namespace dlls::codecs::vcodec_mjpg::syn
