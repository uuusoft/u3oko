#pragma once
/**
\file       flip_y.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_block
*/

namespace libs::optim::s16bit::block::flip_y
{
void alu (::libs::optim::io::MCallInfo& info);
void sse1 (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
void neon (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::block::flip_y
