#pragma once
/**
\file       freq_dct_b8x8_backward.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/

namespace libs::optim::s16bit::freq::dct::b8x8::backward
{
void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
void neon_impl (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::freq::dct::b8x8::backward
