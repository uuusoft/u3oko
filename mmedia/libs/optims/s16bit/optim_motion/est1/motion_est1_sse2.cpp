/**
\file     motion_est1_sse2.cpp
\author   Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date     28.08.2016
\project  u3_optim_libs_motion
\brief    Оценка движения в кадре
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "motion_est1.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buf_helpers_funcs.hpp"
#include "move_alg.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::motion::est1
{
void
sse2 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  alu (info);
}
}   // namespace libs::optim::s16bit::motion::est1

#endif
