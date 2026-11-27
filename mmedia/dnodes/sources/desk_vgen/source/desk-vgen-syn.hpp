#pragma once
/**
\file       desk-vgen-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/

namespace dnodes::sources::desk_vgen::syn
{
using SourceImplInfo  = ::dnodes::sources::gen_lib::SourceImplInfo;
using IBlockMem       = ::libs::utility::mem::IBlockMem;
using DataSourceInfo  = ::libs::events_media::events::DataSourceInfo;
using pkeys2bufs_type = ::dnodes::sources::gen_lib::syn::pkeys2bufs_type;
using tevents_type    = ::dnodes::sources::gen_lib::syn::tevents_type;
using CpuExts         = ::libs::utility::sys::cpu::CpuExts;
}   // namespace dnodes::sources::desk_vgen::syn
