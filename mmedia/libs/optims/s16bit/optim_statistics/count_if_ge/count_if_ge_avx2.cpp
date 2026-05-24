/**
\file       count_if_ge_avx2.cpp
\date       01.05.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_statistic
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "count_if_ge.hpp"
#include "count_if_ge_int.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::statistics::count_if_ge
{
void
avx2 (::libs::optim::io::MCallInfo& cinfo)
{
  U3_ASSERT_TODO_OPTIM;
  avx1 (cinfo);
}
}   // namespace libs::optim::s16bit::statistics::count_if_ge

#endif
