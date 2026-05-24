/**
\file       noise_remove_var3_avx2.cpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_filter
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "noise_remover3_x86.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::filter::noise::var3
{

void
avx2 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  return avx1 (info);
}

}   // namespace libs::optim::s16bit::filter::noise::var3

#endif
