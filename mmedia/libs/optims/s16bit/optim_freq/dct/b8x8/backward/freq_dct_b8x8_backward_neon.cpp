/**
\file       freq_dct_b8x8_backward_neon.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "freq_dct_b8x8_backward.hpp"
#include "freq_dct_b8x8_backward_int.hpp"

#if defined(U3_CPU_ARM)

namespace libs::optim::s16bit::freq::dct::b8x8::backward
{
U3_SET_TARGET_CPU (+simd)
void
neon_impl (::libs::optim::io::MCallInfo& info)
{
  alu (info);
}
}   // namespace libs::optim::s16bit::freq::dct::b8x8::backward

#endif
