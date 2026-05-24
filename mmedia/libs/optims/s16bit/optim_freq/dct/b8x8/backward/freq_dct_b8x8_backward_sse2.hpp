#pragma once
/**
\file       freq_dct_b8x8_backward_sse2.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::freq::dct::b8x8::backward
{
void mmx_b8x8 (short *blk);
void sse2_b8x8 (short *blk);
}   // namespace libs::optim::s16bit::freq::dct::b8x8::backward

#endif
