/**
\file       create_image_y1_avx1.cxx
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq

GenerateImageFromYConstSignedWordXXXFunct
Dp[ x, y ] = unsighsat( Const2 - 2 * ( Const1 - y ) * ( Const1 - y ) )
*/
#include "create_image_y1.hpp"

// old shit
namespace libs::optim::s16bit::gen::create_image1
{
#if 0
#  if defined(U3_CPU_X86)
#    ifndef SET_UNALIGNED_FUNCT
	void avx1 ( ::libs::optim::io::MCallInfo& info )
	{
		U3_ASSERTSIG_OPTIM;
		return udest_sse2( info );
	}
#    endif
#  endif
#endif
}   // namespace libs::optim::s16bit::gen::create_image1
