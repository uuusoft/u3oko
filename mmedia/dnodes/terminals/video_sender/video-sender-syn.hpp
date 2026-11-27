#pragma once
/**
\file       video-sender-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/

namespace dnodes::terminals::video_sender::syn
{
using Buff2ModuleInfo        = ::libs::events_base::props::base_id::Buff2ModuleInfo;
using persisent_id_link_type = ::libs::events_base::props::base_id::persisent_id_link_type;
using EndPointProp           = ::libs::events_base::props::terminals::EndPointProp;
using IBaseId                = ::libs::events_base::runtime::interf::interfaces::IBaseId;
using IEvent                 = ::libs::events::IEvent;
using WrapperHttpEvent       = ::libs::events_http::events::WrapperHttpEvent;
using ZipDataEvent           = ::libs::events_base::runtime::mem::ZipDataEvent;
using FrameDone              = ::libs::events_base::runtime::video::FrameDone;
using WriteData              = ::libs::events_storage::events::WriteData;
using UpdateStream           = ::libs::events_storage::events::UpdateStream;
using IVideoBuf              = ::utils::dbufs::video::IVideoBuf;
using TransformInfo          = ::libs::icore::impl::base::obj::dll::TransformInfo;
using CallInterfInfo         = ::libs::icore::impl::base::obj::dll::CallInterfInfo;
using FilterInfo             = ::libs::icore::impl::base::obj::FilterInfo;
using ConnectInfo            = ::libs::icore::impl::base::obj::ConnectInfo;
using CallSyncs              = ::libs::link::details::CallSyncs;
using Calls                  = ::libs::link::details::Calls;
using ILinksProperty         = ::libs::properties::vers::links::ILinksProperty;

namespace mids = libs::properties::vers::links::mids;
}   // namespace dnodes::terminals::video_sender::syn
