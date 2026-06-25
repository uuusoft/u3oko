#pragma once
/**
\file       fake-vgen-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.09.2018
\project    u3_fake_vgen
*/

namespace dlls::sources::fake_vgen::syn
{
using DataSourceInfo          = ::libs::imdata_events::events::DataSourceInfo;
using IHardwareCapture        = ::dlls::sources::gen_lib::interfs::IHardwareCapture;
using SourceImplInfo          = ::dlls::sources::gen_lib::SourceImplInfo;
using pkeys2bufs_type         = ::dlls::sources::gen_lib::syn::pkeys2bufs_type;
using tevents_type            = ::dlls::sources::gen_lib::syn::tevents_type;
using DefaultFileMask         = ::libs::helpers::files::DefaultFileMask;
using CpuExts                 = ::libs::helpers::sys::cpu::CpuExts;
using IEvent                  = ::libs::events::IEvent;
using InterfCaptureImageEvent = ::libs::ievents::runtime::interf::InterfCaptureImageEvent;
using IBlockMem               = ::libs::helpers::mem::IBlockMem;
using id_val                  = ::libs::helpers::uids::minor::id_val;
}   // namespace dlls::sources::fake_vgen::syn
