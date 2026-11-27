#pragma once
/**
\file       base_id-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       16.07.2018
*/

namespace dnodes::base_id::syn
{
using IEvent            = ::libs::events::IEvent;
using BaseIdProp        = ::libs::events_base::props::base_id::BaseIdProp;
using InterfBaseIdEvent = ::libs::events_base::runtime::interf::InterfBaseIdEvent;
using source_name_type  = ::libs::events_base::props::base_id::source_name_type;
using off_buf_type      = ::utils::dbufs::video::consts::offs::off_buf_type;
using TransformInfo     = ::libs::icore::impl::base::obj::dll::TransformInfo;
using CallInterfInfo    = ::libs::icore::impl::base::obj::dll::CallInterfInfo;
using FilterInfo        = ::libs::icore::impl::base::obj::FilterInfo;
using ConnectInfo       = ::libs::icore::impl::base::obj::ConnectInfo;
}   // namespace dnodes::base_id::syn
