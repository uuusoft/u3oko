#pragma once
/**
\file       all2hsl-dll-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_all2hsl
*/

namespace dlls::convertors::all2hsl::syn
{
using VideoConvertProp   = ::libs::events_base::props::videos::generic::convert::VideoConvertProp;
using IVideoBuf          = ::utils::dbufs::video::IVideoBuf;
using IEvent             = ::libs::events::IEvent;
using AddEvent2EventsMsg = ::libs::events_msg::events::AddEvent2EventsMsg;
using TransformInfo      = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo     = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo         = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo        = ::libs::icore::impl::var1::obj::ConnectInfo;
using mem_var_type       = ::utils::dbufs::IBuf::mem_var_type;
using Dims               = ::utils::dbufs::video::Dims;
using MemVars            = ::utils::dbufs::MemVars;
using Accuracys          = ::libs::events_base::props::videos::generic::convert::Accuracys;

namespace offs = ::utils::dbufs::video::consts::offs;
}   // namespace dlls::convertors::all2hsl::syn
