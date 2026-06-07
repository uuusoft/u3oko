/**
\file       nv21_y16_sse2.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "nv21_y16.hpp"
#include "nv21_y16_int.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::convert::nv21_y16
{
U3_SET_TARGET_CPU (sse2)
void
sse2 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  alu (info);
}
}   // namespace libs::optim::convert::nv21_y16

#endif
