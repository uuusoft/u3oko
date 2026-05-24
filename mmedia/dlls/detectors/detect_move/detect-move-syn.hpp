#pragma once
/**
\file       detect-move-syn.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_detect_move
*/

namespace dlls::detectors::detect_move::syn
{
using VideoDetectProp       = ::libs::ievents::props::videos::generic::detect::VideoDetectProp;
using VideoMorphologyProp   = ::libs::ievents::props::videos::generic::morph::VideoMorphologyProp;
using VideoDiffProp         = ::libs::ievents::props::videos::gens::diff::VideoDiffProp;
using MorphOperationParams  = ::libs::ievents::props::videos::generic::morph::MorphOperationParams;
using MorphBuffInfo         = ::libs::ievents::props::videos::generic::morph::MorphBuffInfo;
using IEvent                = ::libs::events::IEvent;
using InfoBuffVideoDiffProp = ::libs::ievents::props::videos::gens::diff::InfoBuffVideoDiffProp;
using IVideoBuf             = ::utils::dbufs::video::IVideoBuf;
using AddEvent2Base         = ::libs::ievents_events::events::AddEvent2Base;
using DetectViolation       = ::libs::ievents::runtime::video::DetectViolation;
using TransformInfo         = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo        = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo            = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo           = ::libs::icore::impl::var1::obj::ConnectInfo;
}   // namespace dlls::detectors::detect_move::syn
