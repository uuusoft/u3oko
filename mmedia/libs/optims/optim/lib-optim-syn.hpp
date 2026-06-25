#pragma once
/**
\file       lib-optim-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_optim_lib
*/

namespace libs::optim::syn
{
using CpuExts       = ::libs::helpers::sys::cpu::CpuExts;
using IVideoBuf     = ::utils::dbufs::video::IVideoBuf;
using ExpandedTimes = ::libs::helpers::statistic::ExpandedTimes;
using AddOpTime     = ::libs::helpers::statistic::helpers::functors::AddOpTime;
}   // namespace libs::optim::syn
