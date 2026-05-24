/**
\file       matrix1_avx1.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "matrix1.hpp"

//  old shit
namespace libs::optim::s16bit::gen::matrix1
{
#if 0
#  if defined(U3_CPU_X86)
void
avx1 (::libs::optim::io::MCallInfo& info)
{
  U3_CHECK (check (info));
  U3_ASSERT_SIGNAL ("failed");
  return;
}
#  endif
#endif
}   // namespace libs::optim::s16bit::gen::matrix1
