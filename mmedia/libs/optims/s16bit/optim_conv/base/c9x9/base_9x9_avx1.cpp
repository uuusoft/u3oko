/**
\file       *.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017

\project    u3_optim_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "base_9x9.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::conv::base::c9x9
{
U3_SET_TARGET_CPU (avx)
void
mod_avx1 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  mod_sse2 (info);
  _mm256_zeroupper ();
}


U3_SET_TARGET_CPU (avx)
void
avx1 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  sse2 (info);
  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::conv::base::c9x9

#endif
