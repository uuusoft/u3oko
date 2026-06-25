/**
\file       x8_x16_sse2.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "x8_x16.hpp"
#include "x8_x16_int.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::convert::x8_x16
{
U3_SET_TARGET_CPU (sse2)
void
sse2 (::libs::optim::io::MCallInfo& info)
{
#  if 1
  alu (info);
#  else
  X16_TO_X8_PREFIX (8);

  const __m128i mask = _mm_setr_epi16 (0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF);

  for (std::size_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::size_t indx_x = 0; indx_x < width; indx_x += ppc)
    {
      __m128i data = _mm_load_si128 (::libs::helpers::casts::reinterpret_cast_helper< const __m128i* > (yuy2_buf));

      data = _mm_and_si128 (data, mask);

      _mm_store_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (y16_buf), data);

      yuy2_buf += dppc;
      y16_buf += ppc;
    }

    yuy2_buf = ::libs::helpers::mem::move_cptr (yuy2_buf, leak_yuy2);
    y16_buf  = ::libs::helpers::mem::move_ptr (y16_buf, leak_y16);
  }
#  endif
}
}   // namespace libs::optim::convert::x8_x16

#endif
