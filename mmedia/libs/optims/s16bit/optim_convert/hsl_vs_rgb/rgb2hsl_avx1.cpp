/**
\file       rgb2hsl_avx1.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create     27.11.2016
\project    u3_optim_convert
\brief      Набор функция для конвертации HSL <---> RGB16
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "rgb_to_hsl_int.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
U3_SET_TARGET_CPU (avx)
void
rgb24_to_hsl_avx1 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  rgb24_to_hsl_sse2 (info);
  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
