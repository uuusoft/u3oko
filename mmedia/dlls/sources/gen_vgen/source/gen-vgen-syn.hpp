#pragma once
/**
\file       gen-vgen-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       02.03.2026
\project    u3_gen_vgen
*/

namespace dlls::sources::gen_vgen::syn
{
using VideoDriverProp          = ::libs::events_base::props::videos::generic::driver::VideoDriverProp;
using VideoDriverCaptureProp   = ::libs::events_base::props::videos::generic::driver::VideoDriverCaptureProp;
using LinksVideoDriverProp     = ::libs::events_base::props::videos::generic::driver::LinksVideoDriverProp;
using SystemSpecificDriverProp = ::libs::events_base::runtime::video::SystemSpecificDriverProp;
using ICaptureImage            = ::libs::events_base::runtime::interf::interfaces::ICaptureImage;
using ChangeStateProcessEvent  = ::libs::events_base::runtime::state::ChangeStateProcessEvent;
using IVideoBuf                = ::utils::dbufs::video::IVideoBuf;
using ListDevicesDataEvent     = ::libs::events_media::events::ListDevicesDataEvent;
using IInterfGraphObj          = ::libs::core::graph::IInterfGraphObj;
using IEmptyInterfObjGraph     = ::libs::icore::impl::var1::obj::interfs::IEmptyInterfObjGraph;
using BufsEvent                = ::libs::events_base::runtime::mem::BufsEvent;
using tevents_type             = ::dlls::sources::gen_lib::syn::tevents_type;
using TransformInfo            = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo           = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo               = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo              = ::libs::icore::impl::var1::obj::ConnectInfo;
}   // namespace dlls::sources::gen_vgen::syn
