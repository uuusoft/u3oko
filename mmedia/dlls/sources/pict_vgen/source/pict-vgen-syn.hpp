#pragma once
/**
\file       pict-vgen-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       11.03.2026
\project    u3_pict_vgen
*/

namespace dlls::sources::pict_vgen::syn
{
using IHardwareCapture        = ::dlls::sources::gen_lib::interfs::IHardwareCapture;
using SourceImplInfo          = ::dlls::sources::gen_lib::SourceImplInfo;
using pkeys2bufs_type         = ::dlls::sources::gen_lib::syn::pkeys2bufs_type;
using tevents_type            = ::dlls::sources::gen_lib::syn::tevents_type;
using DefaultFileMask         = ::libs::helpers::files::DefaultFileMask;
using CpuExts                 = ::libs::helpers::sys::cpu::CpuExts;
using IEvent                  = ::libs::events::IEvent;
using InterfCaptureImageEvent = ::libs::ievents::runtime::interf::InterfCaptureImageEvent;
using IBlockMem               = ::libs::helpers::mem::IBlockMem;
}   // namespace dlls::sources::pict_vgen::syn
