#pragma once
/**
\file       gt_const1_mull_add.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_bits

D[i] = D[i] + D[i] * D[i] *(S[i] > Const1 ? 1 : 0 )
*/

namespace libs::optim::s16bit::bits::cmp::gt_const1_mull_add
{
void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void udest_sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::bits::cmp::gt_const1_mull_add
