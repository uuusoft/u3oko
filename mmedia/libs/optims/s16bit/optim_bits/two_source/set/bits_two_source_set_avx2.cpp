/**
\file       bits_two_source_set_avx2.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_bits
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "../bits_two_source_move_alg.hpp"
#include "bits_two_source_set_ops.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::bits::two_source::set
{
U3_SET_TARGET_CPU (avx2)
void
avx2 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  avx1 (info);
}
}   // namespace libs::optim::s16bit::bits::two_source::set

#endif
