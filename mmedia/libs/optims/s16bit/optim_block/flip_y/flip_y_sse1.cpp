/**
\file       flip_y_sse1.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_block
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "flip_y.hpp"
#include "flip_y_move_alg.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::block::flip_y
{
U3_SET_TARGET_CPU (sse)
void
sse1 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  alu (info);
}
}   // namespace libs::optim::s16bit::block::flip_y

#endif
