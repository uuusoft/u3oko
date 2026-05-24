/**
\file       scale_nearest_avx1.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_scale
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "scale_nearest.hpp"
#include "scale_nearest_int.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::scale::flow::wany::nearest
{
U3_SET_TARGET_CPU (avx)
void
avx1 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  sse2 (info);
  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::scale::flow::wany::nearest
#endif
