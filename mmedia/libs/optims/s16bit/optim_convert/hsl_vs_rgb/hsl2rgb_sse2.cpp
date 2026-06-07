/**
\file       hsl2rgb_sse2.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.11.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "hsl_to_rgb_int.hpp"

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
#ifdef U3_CPU_X86

U3_SET_TARGET_CPU (sse2)
void
hsl_to_rgb24_sse2 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  hsl_to_rgb24_sse1 (info);
  // #  if defined(U3_CPU_X86_64)
  //   hsl_to_rgb24_alu (info);
  // #  else
  //   hsl_to_rgb24_sse1 (info);
  // #  endif
}

#endif
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb
