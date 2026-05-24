#pragma once
/**
\file       gen-vgen-syn.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       02.03.2026
\project    u3_gen_vgen
*/

namespace dlls::sources::gen_vgen::syn
{
using VideoDriverProp          = ::libs::ievents::props::videos::generic::driver::VideoDriverProp;
using VideoDriverCaptureProp   = ::libs::ievents::props::videos::generic::driver::VideoDriverCaptureProp;
using LinksVideoDriverProp     = ::libs::ievents::props::videos::generic::driver::LinksVideoDriverProp;
using SystemSpecificDriverProp = ::libs::ievents::runtime::video::SystemSpecificDriverProp;
using ICaptureImage            = ::libs::ievents::runtime::interf::interfaces::ICaptureImage;
using ChangeStateProcessEvent  = ::libs::ievents::runtime::state::ChangeStateProcessEvent;
using IVideoBuf                = ::utils::dbufs::video::IVideoBuf;
using ListDevicesDataEvent     = ::libs::imdata_events::events::ListDevicesDataEvent;
using IInterfGraphObj          = ::libs::core::graph::IInterfGraphObj;
using IEmptyInterfObjGraph     = ::libs::icore::impl::var1::obj::interfs::IEmptyInterfObjGraph;
using BufsEvent                = ::libs::ievents::runtime::mem::BufsEvent;
using tevents_type             = ::dlls::sources::gen_lib::syn::tevents_type;
using TransformInfo            = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo           = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo               = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo              = ::libs::icore::impl::var1::obj::ConnectInfo;
}   // namespace dlls::sources::gen_vgen::syn
