#pragma once
/**
\file       fake-vgen-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.09.2018
\project    u3_fake_vgen
*/

namespace dlls::sources::fake_vgen::syn
{
using DataSourceInfo          = ::libs::events_media::events::DataSourceInfo;
using IHardwareCapture        = ::dlls::sources::gen_lib::interfs::IHardwareCapture;
using SourceImplInfo          = ::dlls::sources::gen_lib::SourceImplInfo;
using pkeys2bufs_type         = ::dlls::sources::gen_lib::syn::pkeys2bufs_type;
using tevents_type            = ::dlls::sources::gen_lib::syn::tevents_type;
using DefaultFileMask         = ::libs::utility::files::DefaultFileMask;
using CpuExts                 = ::libs::utility::sys::cpu::CpuExts;
using IEvent                  = ::libs::events::IEvent;
using InterfCaptureImageEvent = ::libs::events_base::runtime::interf::InterfCaptureImageEvent;
using IBlockMem               = ::libs::utility::mem::IBlockMem;
using id_val                  = ::libs::utility::uids::minor::id_val;
using mem_var_type            = ::utils::dbufs::IBuf::mem_var_type;
using Dims                    = ::utils::dbufs::video::Dims;
using MemVars                 = ::utils::dbufs::MemVars;
}   // namespace dlls::sources::fake_vgen::syn
