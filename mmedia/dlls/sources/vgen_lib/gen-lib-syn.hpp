#pragma once
/**
\file       gen-lib-syn.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.06.2018
\project    u3_vgen_lib
*/

namespace dlls::sources::gen_lib::syn
{
using tevents_type             = std::list< ::libs::events::IEvent::ptr >;
using keys2bufs_type           = std::unordered_map< ::utils::dbufs::video::consts::offs::off_buf_type, ::utils::dbufs::video::IVideoBuf::ptr >;
using pkeys2bufs_type          = std::shared_ptr< keys2bufs_type >;
using VideoDriverProp          = ::libs::ievents::props::videos::generic::driver::VideoDriverProp;
using VideoDriverCaptureProp   = ::libs::ievents::props::videos::generic::driver::VideoDriverCaptureProp;
using LinksVideoDriverProp     = ::libs::ievents::props::videos::generic::driver::LinksVideoDriverProp;
using VideoCorrectProp         = ::libs::ievents::props::videos::generic::correct::VideoCorrectProp;
using SystemSpecificDriverProp = ::libs::ievents::runtime::video::SystemSpecificDriverProp;
using CpuExts                  = ::libs::helpers::sys::cpu::CpuExts;
using IVideoBuf                = ::utils::dbufs::video::IVideoBuf;
using ICorrectImage            = ::libs::ievents::runtime::interf::interfaces::ICorrectImage;
using ICaptureImage            = ::libs::ievents::runtime::interf::interfaces::ICaptureImage;
using DataSourceInfo           = ::libs::imdata_events::events::DataSourceInfo;
}   // namespace dlls::sources::gen_lib::syn
