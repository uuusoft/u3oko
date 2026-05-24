/**
\file
\author    Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create    27.07.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb2.hpp"
#include "rgb_to_l_int2.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::convert::l_vs_rgb2
{
U3_SET_TARGET_CPU (avx)
void
rgb24_to_l_avx1 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  return rgb24_to_l_alu (info);
#  if 0
    _mm256_zeroupper();
    rgb24_to_l_sse2 ( info );
    _mm256_zeroupper();
#  endif
}
}   // namespace libs::optim::s16bit::convert::l_vs_rgb2

#endif
