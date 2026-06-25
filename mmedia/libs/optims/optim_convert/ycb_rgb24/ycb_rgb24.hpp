#pragma once
/**
\file       ycb_rgb24.hpp
\author     Erashov Anton erashov2026@proton.me
\date       30.07.2018
\project    u3_optim_gen_convert
*/

namespace libs::optim::convert::ycb_rgb24
{
void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
void neon (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::convert::ycb_rgb24
