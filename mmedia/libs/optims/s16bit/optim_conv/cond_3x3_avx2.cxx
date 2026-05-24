/**
\file				cond_3x3_sse.cxx
\author			Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date				01.01.2017
\project		u3_optim_conv
*/

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::conv::cond
{
// OUT[x,y] = IN[x,y] * ( CONDT[x,y] < bound ? mask1 : mask2 )
#  ifdef MODUL_2D_CONV_IMPL
U3_SET_TARGET_CPU (avx2)
void
mod_cond_b3x3_avx2 (::libs::optim::io::MCallInfo& info)
#  else
U3_SET_TARGET_CPU (avx2)
void
cond_b3x3_avx2 (::libs::optim::io::MCallInfo& info)
#  endif
{
  U3_ASSERT_TODO_OPTIM;

  _mm256_zeroupper ();
#  ifdef MODUL_2D_CONV_IMPL
  mod_cond_b3x3_avx1 (info);
#  else
  cond_b3x3_avx1 (info);
#  endif

  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::conv::cond

#endif
