/**
\file       freq_dct_b8x8_backward_alu.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "freq_dct_b8x8_backward.hpp"
#include "freq_dct_b8x8_backward_int.hpp"
#include "freq_dct_b8x8_backward_alu.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::backward
{
struct TTDCT8x8_ALU {
  TTDCT8x8_ALU ()
  {
  }

  void
  operator() (std::int16_t* buf)
  {
#ifdef U3_FAKE_DISABLE
    std::int16_t tbuf[64];

    std::copy (buf, buf + 64, tbuf);
    alu_b8x8 (tbuf);
    volatile bool test = false;
    test;

#else
    alu_b8x8 (buf);
#endif
  }
};


void
alu (::libs::optim::io::MCallInfo& info)
{
  freq_dct_b8x8_backward< TTDCT8x8_ALU > (info);
}
}   // namespace libs::optim::s16bit::freq::dct::b8x8::backward
