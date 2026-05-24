/**
\file       gradient1_avx1.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "graduent1.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::gen::graduent1
{
void
avx1 (::libs::optim::io::MCallInfo& cinfo)
{
  U3_ASSERT_TODO_OPTIM;
  sse2 (cinfo);
}
}   // namespace libs::optim::s16bit::gen::graduent1

#endif
