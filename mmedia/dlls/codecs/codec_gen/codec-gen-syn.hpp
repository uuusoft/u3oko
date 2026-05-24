#pragma once
/**
\file       codec-gen-syn.hpp
\date       01.05.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_codec_gen
*/

namespace dlls::codecs::codec_gen::syn
{
using VideoCodecFlatProp = ::libs::ievents::props::videos::generic::codec::VideoCodecFlatProp;
using TransformInfo      = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using VideoCodecProp     = ::libs::ievents::props::videos::generic::codec::VideoCodecProp;
using NodeID             = ::libs::core::graph::NodeID;
using CpuExts            = ::libs::helpers::sys::cpu::CpuExts;
}   // namespace dlls::codecs::codec_gen::syn
