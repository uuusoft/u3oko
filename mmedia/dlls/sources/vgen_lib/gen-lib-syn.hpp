#pragma once
/**
\file       gen-lib-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.06.2018
*/

namespace dlls::sources::gen_lib::syn
{
using tevents_type             = std::list< ::libs::events::IEvent::ptr >;
using persistent_off_buf_type  = ::utils::dbufs::video::consts::offs::persistent_off_buf_type;
using keys2bufs_type           = boost::unordered_flat_map< persistent_off_buf_type, ::utils::dbufs::video::IVideoBuf::ptr, ::libs::utility::utils::TransparentStringHash, std::equal_to<> >;
using pkeys2bufs_type          = std::shared_ptr< keys2bufs_type >;
using VideoDriverProp          = ::libs::events_base::props::videos::generic::driver::VideoDriverProp;
using VideoDriverCaptureProp   = ::libs::events_base::props::videos::generic::driver::VideoDriverCaptureProp;
using LinksVideoDriverProp     = ::libs::events_base::props::videos::generic::driver::LinksVideoDriverProp;
using VideoCorrectProp         = ::libs::events_base::props::videos::generic::correct::VideoCorrectProp;
using SystemSpecificDriverProp = ::libs::events_base::runtime::video::SystemSpecificDriverProp;
using CpuExts                  = ::libs::utility::sys::cpu::CpuExts;
using IVideoBuf                = ::utils::dbufs::video::IVideoBuf;
using ICorrectImage            = ::libs::events_base::runtime::interf::interfaces::ICorrectImage;
using ICaptureImage            = ::libs::events_base::runtime::interf::interfaces::ICaptureImage;
using DataSourceInfo           = ::libs::events_media::events::DataSourceInfo;
}   // namespace dlls::sources::gen_lib::syn
