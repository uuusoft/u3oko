#pragma once
/**
\file       detect-face-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_detect_face
*/

namespace dlls::detectors::detect_face::syn
{
using IVideoBuf       = ::utils::dbufs::video::IVideoBuf;
using VideoDetectProp = ::libs::ievents::props::videos::generic::detect::VideoDetectProp;
using TransformInfo   = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo  = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo      = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo     = ::libs::icore::impl::var1::obj::ConnectInfo;
using FaceDetect      = ::libs::ievents::runtime::video::FaceDetect;
using ProxyBuf        = ::libs::optim::io::ProxyBuf;
using IEvent          = ::libs::events::IEvent;
using AddEvent2Base   = ::libs::ievents_events::events::AddEvent2Base;
}   // namespace dlls::detectors::detect_face::syn
