/**
\file       gradient1_avx2.cxx
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/
#include "gradient1.hpp"
// old shit
namespace libs
{
namespace optim
{
namespace s16bit
{
namespace gen
{
namespace gradient1
{
#if 0
#  if defined(U3_CPU_X86)
#    ifndef SET_UNALIGNED_FUNCT
	void avx2 ( ::libs::optim::io::MCallInfo& info )
	{
		U3_ASSERTSIG_OPTIM;
		return avx1 ( info );
	}
#    endif
#  endif
#endif
}   // namespace gradient1
}   // namespace gen
}   // namespace s16bit
}   // namespace optim
}   // namespace libs
