#pragma once
/**
\file       vcodec-mjpg-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_vcodec_mjpg
*/

namespace dlls::codecs::vcodec_mjpg::syn
{
using VideoCodecProp = ::libs::events_base::props::videos::generic::codec::VideoCodecProp;
using TransformInfo  = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using VideoCodecProp = ::libs::events_base::props::videos::generic::codec::VideoCodecProp;
using IVideoBuf      = ::utils::dbufs::video::IVideoBuf;
using StatisticInfo  = ::dlls::codecs::codec_gen::StatisticInfo;
using AllocParams    = ::utils::dbufs::video::AllocParams;
using HeaderIFrame   = ::dlls::codecs::codec_gen::HeaderIFrame;
using IMCaller       = ::libs::optim::mcalls::IMCaller;
}   // namespace dlls::codecs::vcodec_mjpg::syn
