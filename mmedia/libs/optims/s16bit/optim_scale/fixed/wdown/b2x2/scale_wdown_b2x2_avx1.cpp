/**
\file       scale_wdown_b2x2_avx1.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_scale
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "scale_wdown_b2x2.hpp"
#include "scale_wdown_b2x2_int.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::scale::fixed::wdown::b2x2
{
void
avx1 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  sse2 (info);
}
}   // namespace libs::optim::s16bit::scale::fixed::wdown::b2x2

#endif
