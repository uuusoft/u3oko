/**
\file       sharp1_sse1.cxx
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_filter
\brief
*/
#include "sharp1.hpp"
// old shit

namespace libs
{
namespace optim
{
namespace s16bit
{
namespace filter
{
namespace sharp1
{
#if 0
#  if defined(U3_CPU_X86)
#    ifndef SET_UNALIGNED_FUNCT
	void sse1 (
#    else
	void udest_sse1 (
#    endif
		::libs::optim::io::MCallInfo& info )
	{
		return mmx ( info );
	}
#  endif
#endif
}   // namespace sharp1
}   // namespace filter
}   // namespace s16bit
}   // namespace optim
}   // namespace libs
