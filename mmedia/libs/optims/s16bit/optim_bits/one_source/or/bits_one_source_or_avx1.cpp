/**
\file       bits_one_source_or_avx1.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.07.2017

\project    u3_optim_libs_bits
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "bits_one_source_or_ops.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::bits::one_source::or_op
{
U3_SET_TARGET_CPU (avx)
void
avx1 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  _mm256_zeroall ();
  sse2 (info);
  _mm256_zeroall ();
}
}   // namespace libs::optim::s16bit::bits::one_source::or_op

#endif
