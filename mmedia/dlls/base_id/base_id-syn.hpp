#pragma once
/**
\file       base_id-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       16.07.2018
\project    u3_base_id_dll
*/

namespace dlls::base_id::syn
{
using IEvent            = ::libs::events::IEvent;
using BaseIdProp        = ::libs::ievents::props::base_id::BaseIdProp;
using InterfBaseIdEvent = ::libs::ievents::runtime::interf::InterfBaseIdEvent;
using source_name_type  = ::libs::ievents::props::base_id::source_name_type;
using off_buf_type      = ::utils::dbufs::video::consts::offs::off_buf_type;
using TransformInfo     = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo    = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo        = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo       = ::libs::icore::impl::var1::obj::ConnectInfo;
}   // namespace dlls::base_id::syn
