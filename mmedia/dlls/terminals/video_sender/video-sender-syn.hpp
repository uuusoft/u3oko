#pragma once
/**
\file       video-sender-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_video_sender_dll
*/

namespace dlls::terminals::video_sender::syn
{
using Buff2ModuleInfo  = ::libs::ievents::props::base_id::Buff2ModuleInfo;
using id_link_type     = ::libs::ievents::props::base_id::id_link_type;
using EndPointProp     = ::libs::ievents::props::terminals::EndPointProp;
using IBaseId          = ::libs::ievents::runtime::interf::interfaces::IBaseId;
using IEvent           = ::libs::events::IEvent;
using WrapperHttpEvent = ::libs::ihttp_events::events::WrapperHttpEvent;
using ZipDataEvent     = ::libs::ievents::runtime::mem::ZipDataEvent;
using FrameDone        = ::libs::ievents::runtime::video::FrameDone;
using WriteData        = ::libs::istorage_events::events::WriteData;
using UpdateStream     = ::libs::istorage_events::events::UpdateStream;
using IVideoBuf        = ::utils::dbufs::video::IVideoBuf;
using TransformInfo    = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo   = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo       = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo      = ::libs::icore::impl::var1::obj::ConnectInfo;
using CallSyncs        = ::libs::link::details::CallSyncs;
using Calls            = ::libs::link::details::Calls;
using ILinksProperty   = ::libs::properties::vers::links::ILinksProperty;
}   // namespace dlls::terminals::video_sender::syn
