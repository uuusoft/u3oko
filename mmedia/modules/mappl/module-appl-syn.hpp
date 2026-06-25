#pragma once
/**
\file       module-appl-syn.hpp
\date       12.06.2026
\author     Erashov Anton erashov2026@proton.me
\project    mappl
*/

namespace modules::mappl::syn
{
using CpuInfo           = ::libs::helpers::sys::cpu::CpuInfo;
using CpuExts           = ::libs::helpers::sys::cpu::CpuExts;
using ISysInfo          = ::libs::helpers::sys::ISysInfo;
using InitApplication   = ::libs::link::appl::InitApplication;
using IApplicationProxy = ::libs::link::appl::IApplicationProxy;
using IDemonsProperty   = ::libs::iproperties::vers::demon::IDemonsProperty;
using ISystemProperty   = ::libs::iproperties::vers::system::ISystemProperty;
}   // namespace modules::mappl::syn
