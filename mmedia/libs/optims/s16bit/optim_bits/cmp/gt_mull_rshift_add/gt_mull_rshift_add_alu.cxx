/**
\file       gt_mull_rshift_add_alu.cxx
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_bits
\brief
*/

namespace libs::optim::s16bit::bits::cmp::gt_mull_rshift_add
{

#ifndef SET_UNALIGNED_FUNCT
void
alu (::libs::optim::io::MCallInfo& info)
{
  // D[i] = D[i] + ( (D[i] * ( (S[i] > Const1 ? S[i] : 0) >> 1 ) ) >> Const2 )
}
#endif

}   // namespace libs::optim::s16bit::bits::cmp::gt_mull_rshift_add
