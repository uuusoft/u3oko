#pragma once
/**
\file       bits_one_source_or_ops.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.07.2017

\project    u3_optim_libs_bits
*/

namespace libs::optim::s16bit::bits::one_source::or_op
{
void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void udest_sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::bits::one_source::or_op
