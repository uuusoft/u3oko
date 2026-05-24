/**
\file       create_image_y1_sse2.cxx
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
	void sse2 (
#    else
	void udest_sse2 (
#    endif
		::libs::optim::io::MCallInfo& info )
	{
		U3_CHECK ( check( info ) );

#    ifndef SET_UNALIGNED_FUNCT
		U3_ASSERT( ::libs::helpers::mem::check_align16_ptr ( info.dsts_[0].buf() ) );
		U3_ASSERT( ::libs::helpers::mem::check_align16 ( info.dsts_[0].stride_ ) );
#    endif
		int int_cubcycle = ( (sizeof (std::int16_t) * info.dsts_[0].width_ + 15 ) / 16);
		int leak_stride_dest = info.dsts_[0].stride_ - 16 * int_cubcycle;

		const void*		dest			= info.dsts_[0].buf();
		const int		width_element	= info.dsts_[0].width_;
		const int		height_element	= info.dsts_[0].height_;
		const std::int16_t*	consts1		= info.params_.consts_[0];
		const std::int16_t*	consts2		= info.params_.consts_[1];

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
		 U3_ASSERT_SIGNAL_I64;
		//U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
		__asm
		{
			pushad;

			mov esi, consts1;
			movdqu xmm6, [esi];

			mov esi, consts2;
			movdqu xmm7, [esi];

			; load const 1;
			pxor xmm4, xmm4;
			pcmpeqw xmm0, xmm0;
			psubsw xmm4, xmm0;

			pcmpeqw xmm0, xmm0;
			pxor xmm5, xmm5;

			mov edi, dest;
			mov eax, leak_stride_dest;
			mov ebx, width_element;
			mov edx, height_element;

			cycle1:

			; calculate 2 * (SAD ^ 2 ) for Y in mm1;
			movdqa xmm1, xmm5;
			psubsw xmm1, xmm6;
			pmullw xmm1, xmm1;
			psllw xmm1, 1;

			movdqa xmm0, xmm7;
			psubusw xmm0, xmm1;

			mov ecx, ebx;

			cycle2:

#      ifndef SET_UNALIGNED_FUNCT
			movdqa[edi], xmm0;
#      else
			movdqu[edi], xmm0;
#      endif

			add edi, 16;
			sub ecx, 8;
			jg cycle2;

			paddsw xmm5, xmm4;
			add edi, eax;

			sub edx, 1;

			; 24.05.2016;
			jg cycle1;

			popad;
		}
#    endif
		return;
	}
#  endif
#endif
}   // namespace libs::optim::s16bit::gen::create_image1
