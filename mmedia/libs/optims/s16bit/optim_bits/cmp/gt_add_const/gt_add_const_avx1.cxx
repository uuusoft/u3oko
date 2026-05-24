/**
\file       gt_add_const_mmx.cxx
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_bits
\brief
*/

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::bits::cmp::gt_add_const
{

#  ifndef SET_UNALIGNED_FUNCT
void
avx1 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  udest_sse2 (info);
}
#  endif

}   // namespace libs::optim::s16bit::bits::cmp::gt_add_const

#endif
