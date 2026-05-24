/**
\file       freq_dct_b8x8_forward_sse2.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "freq_dct_b8x8_forward.hpp"
#include "freq_dct_b8x8_forward_int.hpp"
#include "freq_dct_b8x8_forward_sse2.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::freq::dct::b8x8::forward
{
struct TTDCT8x8_SSE2 {
  TTDCT8x8_SSE2 ()
  {
  }

  void
  operator() (std::int16_t* buf)
  {
#  if 0
      std::int16_t tbuf[ 64 ];

      std::copy( buf, buf + 64, tbuf );
      alu_b8x8( tbuf );
      mmx_b8x8 ( buf );
      volatile bool test = false;
      test;

#  else
    mmx_b8x8 (buf);
    // sse2_b8x8( buf );
#  endif
  }
};


U3_SET_TARGET_CPU (sse2)
void
sse2 (::libs::optim::io::MCallInfo& info)
{
  freq_dct_b8x8_forward_generic< TTDCT8x8_SSE2 > (info);
}
}   // namespace libs::optim::s16bit::freq::dct::b8x8::forward

#endif
