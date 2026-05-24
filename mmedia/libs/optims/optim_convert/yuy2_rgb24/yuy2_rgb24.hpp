#pragma once
/**
\file       yuy2_rgb24.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_optim_gen_convert
*/

namespace libs::optim::convert::yuy2_rgb24
{
void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
void neon (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::convert::yuy2_rgb24
