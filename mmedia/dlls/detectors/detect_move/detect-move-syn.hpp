#pragma once
/**
\file       detect-move-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_detect_move
*/

namespace dlls::detectors::detect_move::syn
{
using VideoDetectProp       = ::libs::events_base::props::videos::generic::detect::VideoDetectProp;
using VideoMorphologyProp   = ::libs::events_base::props::videos::generic::morph::VideoMorphologyProp;
using VideoDiffProp         = ::libs::events_base::props::videos::gens::diff::VideoDiffProp;
using MorphOperationParams  = ::libs::events_base::props::videos::generic::morph::MorphOperationParams;
using MorphBuffInfo         = ::libs::events_base::props::videos::generic::morph::MorphBuffInfo;
using IEvent                = ::libs::events::IEvent;
using InfoBuffVideoDiffProp = ::libs::events_base::props::videos::gens::diff::InfoBuffVideoDiffProp;
using IVideoBuf             = ::utils::dbufs::video::IVideoBuf;
using AddEvent2EventsMsg    = ::libs::events_msg::events::AddEvent2EventsMsg;
using DetectViolation       = ::libs::events_base::runtime::video::DetectViolation;
using TransformInfo         = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo        = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo            = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo           = ::libs::icore::impl::var1::obj::ConnectInfo;
using DiffImpl              = ::dlls::gens::vgen_diff::lib::DiffImpl;
using MopsImpl              = ::dlls::gens::vgen_mops::lib::MopsImpl;
}   // namespace dlls::detectors::detect_move::syn
