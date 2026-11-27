#pragma once
/**
\file       codec-gen-syn.hpp
\date       01.05.2018
\author     Erashov Anton erashov2026@proton.me
*/

namespace dnodes::codecs::codec_gen::syn
{
using VideoCodecFlatProp = ::libs::events_base::props::videos::generic::codec::VideoCodecFlatProp;
using TransformInfo      = ::libs::icore::impl::base::obj::dll::TransformInfo;
using VideoCodecProp     = ::libs::events_base::props::videos::generic::codec::VideoCodecProp;
using NodeID             = ::libs::core::graph::NodeID;
using IMCaller           = ::libs::optim::mcalls::IMCaller;
using CpuExts            = ::libs::utility::sys::cpu::CpuExts;
}   // namespace dnodes::codecs::codec_gen::syn
