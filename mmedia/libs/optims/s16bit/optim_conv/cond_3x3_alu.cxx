/**
\file				cond_3x3_alu.cpp
\author			Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date				01.01.2017
\project		u3_optim_conv
*/

namespace libs::optim::s16bit::conv::cond
{
#ifdef MODUL_2D_CONV_IMPL
void
mod_cond_b3x3_alu (::libs::optim::io::MCallInfo& info)
#else
void
cond_b3x3_alu (::libs::optim::io::MCallInfo& info)
#endif
{
  U3_THROW_EXCEPTION ("failed");
}
}   // namespace libs::optim::s16bit::conv::cond
