/**
\file       count_if_ge_neon.cpp
\date       01.05.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_statistic
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "count_if_ge.hpp"
#include "count_if_ge_int.hpp"

#if defined(U3_CPU_ARM)

namespace libs::optim::s16bit::statistics::count_if_ge
{
void
neon (::libs::optim::io::MCallInfo& cinfo)
{
  U3_ASSERT_TODO_OPTIM;
  alu (cinfo);
}
}   // namespace libs::optim::s16bit::statistics::count_if_ge

#endif
