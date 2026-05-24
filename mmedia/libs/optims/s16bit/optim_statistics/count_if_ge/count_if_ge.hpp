#pragma once
/**
\file       count_if_ge.hpp
\date       01.05.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_statistic
*/

namespace libs::optim::s16bit::statistics::count_if_ge
{
void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
void neon (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::statistics::count_if_ge
