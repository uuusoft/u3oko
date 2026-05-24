/**
\file       freq_dct_b8x8_forward_avx2.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "freq_dct_b8x8_forward.hpp"
#include "freq_dct_b8x8_forward_int.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::freq::dct::b8x8::forward
{
U3_SET_TARGET_CPU (avx2)
void
avx2 (::libs::optim::io::MCallInfo& info)
{
  avx1 (info);
}

}   // namespace libs::optim::s16bit::freq::dct::b8x8::forward

#endif
