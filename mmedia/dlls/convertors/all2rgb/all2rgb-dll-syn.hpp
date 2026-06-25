#pragma once
/**
\file       all2rgb-dll-syn.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_all2rgb
*/

namespace dlls::convertors::all2rgb::syn
{
using VideoConvertProp = ::libs::ievents::props::videos::generic::convert::VideoConvertProp;
using IVideoBuf        = ::utils::dbufs::video::IVideoBuf;
using IEvent           = ::libs::events::IEvent;
using AddEvent2Base    = ::libs::ievents_events::events::AddEvent2Base;
using TransformInfo    = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo   = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo       = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo      = ::libs::icore::impl::var1::obj::ConnectInfo;
}   // namespace dlls::convertors::all2rgb::syn
