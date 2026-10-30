/**
\file       nv21_y16_neon.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "nv21_y16.hpp"
#include "nv21_y16_int.hpp"

#ifdef U3_CPU_ARM

namespace libs::optim::convert::nv21_y16
{
U3_SET_TARGET_CPU (+simd)
void
neon (::libs::optim::io::MCallInfo& info)
{
  ::libs::utility::checks::mark_todo ("todo");
  alu (info);
}
}   // namespace libs::optim::convert::nv21_y16

#endif
