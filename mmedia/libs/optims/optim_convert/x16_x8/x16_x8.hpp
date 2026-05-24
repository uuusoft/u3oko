#pragma once
/**
\file       x16_x8.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_gen_convert
*/

namespace libs::optim::convert::x16_x8
{
void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
void neon (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::convert::x16_x8
