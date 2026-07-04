/**
\file       yuy2_y16_avx2.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "yuy2_y16.hpp"
#include "yuy2_y16_int.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::convert::yuy2_y16
{
U3_SET_TARGET_CPU (avx2)
void
avx2 (::libs::optim::io::MCallInfo& info)
{
  YUY22Y16_PREFIX (16);

  _mm256_zeroupper ();

  const __m256i mask = _mm256_setr_epi16 (
    0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF);

  for (std::uint32_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::uint32_t indx_x = 0; indx_x < width; indx_x += ppc)
    {
      __m256i data = _mm256_load_si256 (::libs::utility::casts::reinterpret_cast_helper< const __m256i* > (yuy2_buf));
      data         = _mm256_and_si256 (data, mask);
      _mm256_store_si256 (::libs::utility::casts::reinterpret_cast_helper< __m256i* > (y16_buf), data);

      yuy2_buf += dppc;
      y16_buf += ppc;
    }

    yuy2_buf = ::libs::utility::mem::move_cptr (yuy2_buf, leak_yuy2);
    y16_buf  = ::libs::utility::mem::move_ptr (y16_buf, leak_y16);
  }

  _mm256_zeroupper ();
}
}   // namespace libs::optim::convert::yuy2_y16

#endif
