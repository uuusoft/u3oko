/**
\file       sharp1_alu.cxx
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_filter
\brief
*/
#include "sharp1.hpp"

// old shit
namespace libs::optim::s16bit::filter::sharp1
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

		U3_CHECK ( ( info.dsts_[0].height_ >= 4 ) );

		float temp_f1 = (8.0f + ( info.params_.consts_[0][0] + 3) );
		float temp_f2 = (5.0f + ( info.params_.consts_[0][0] + 3) );
		float temp_f3 = (1.0f / (float )( info.params_.consts_[0][0] + 3) ) * 1024.0f;

		// 26.03.2016 - corrected to std::int16_t conversion
		short array_div[8] =
		{
			(std::int16_t)( temp_f3), (std::int16_t)( temp_f3), (std::int16_t)( temp_f3), (std::int16_t)( temp_f3),
			(std::int16_t)( temp_f3), (std::int16_t)( temp_f3), (std::int16_t)( temp_f3), (std::int16_t)( temp_f3)
		};

		// 26.03.2016 - corrected to std::int16_t conversion
		short array_mull[8] =
		{
			(std::int16_t)( temp_f2 ), (std::int16_t)( temp_f1 ), (std::int16_t)( temp_f1 ), (std::int16_t)( temp_f1 ),
			(std::int16_t)( temp_f1 ), (std::int16_t)( temp_f1 ), (std::int16_t)( temp_f1 ), (std::int16_t)( temp_f2 )
		};

		int loc_number_byte = info.dsts_[0].stride_ * info.dsts_[0].height_;

		const void*	dest			= info.dsts_[0].buf();
		const int	stride_dest	= info.dsts_[0].stride_;

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
		 U3_ASSERT_SIGNAL_I64;
		//U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
		__asm
		{
			pushad;

			mov eax, stride_dest;
			mov ecx, loc_number_byte;

			sub ecx, eax;
			sub ecx, eax;
			shr ecx, 5;

			mov ebx, dest;
			add ebx, eax;

			lea edx, array_mull;
			movdqu xmm6, [edx];

			lea edx, array_div;
			movdqu xmm5, [edx];

			pxor xmm7, xmm7;

			cycle1:
			; mm0, mm1 - current 8 pixel;
			; mm7 - temporarely register[zero ? ];
			; mm6 - main mull koeff - 4 word;
			; mm2, mm3 - temporarely register;
			; mm4 - tempreraly register;
			; load main 8 bytes;
#      ifndef SET_UNALIGNED_FUNCT
			movdqa xmm0, [ebx];
			movdqa xmm1, [ebx + 16];
#      else
			movdqu xmm0, [ebx];
			movdqu xmm1, [ebx + 16];
#      endif

			movdqa xmm2, xmm0;
			movdqa xmm3, xmm1;

			; mull 8 words to main koeff;
			pmullw xmm0, xmm6;
			pmullw xmm1, xmm6;

			; sub horizontal picter - ? ? ? ? ;
			movdqa xmm4, xmm2;
			pslldq xmm4, 2;
			psubsw xmm0, xmm4;
			movdqa xmm4, xmm2;
			psrldq xmm4, 2;
			psubsw xmm0, xmm4;

			movdqa xmm4, xmm3;
			pslldq xmm4, 2;
			psubsw xmm1, xmm4;
			movdqa xmm4, xmm3;
			psrldq xmm4, 2;
			psubsw xmm1, xmm4;

			; load upper 8 pixel;
			sub ebx, eax;
#      ifndef SET_UNALIGNED_FUNCT
			movdqa xmm2, [ebx];
			movdqa xmm3, [ebx + 16];
#      else
			movdqu xmm2, [ebx];
			movdqu xmm3, [ebx + 16];
#      endif
			add ebx, eax;

			; add upper picter - ? ? ? ? ;
			movdqa xmm4, xmm2;
			psubsw xmm0, xmm4;
			pslldq xmm4, 2;
			psubsw xmm0, xmm4;
			movdqa xmm4, xmm2;
			psrldq xmm4, 2;
			psubsw xmm0, xmm4;

			movdqa xmm4, xmm3;
			psubsw xmm1, xmm4;
			pslldq xmm4, 2;
			psubsw xmm1, xmm4;
			movdqa xmm4, xmm3;
			psrldq xmm4, 2;
			psubsw xmm1, xmm4;

			; load lower 8 pixel;
			add ebx, eax;
#      ifndef SET_UNALIGNED_FUNCT
			movdqa xmm2, [ebx];
			movdqa xmm3, [ebx + 16];
#      else
			movdqu xmm2, [ebx];
			movdqu xmm3, [ebx + 16];
#      endif
			sub ebx, eax;

			; add lower picter - ? ? ? ? ;
			movdqa xmm4, xmm2;
			psubsw xmm0, xmm4;
			pslldq xmm4, 2;
			psubsw xmm0, xmm4;
			movdqa xmm4, xmm2;
			psrldq xmm4, 2;
			psubsw xmm0, xmm4;

			movdqa xmm4, xmm3;
			psubsw xmm1, xmm4;
			pslldq xmm4, 2;
			psubsw xmm1, xmm4;
			movdqa xmm4, xmm3;
			psrldq xmm4, 2;
			psubsw xmm1, xmm4;

			; calculate average - div from mull and shift;
			movdqa xmm4, xmm0;
			pmullw xmm0, xmm5;
			pmulhw xmm4, xmm5;
			movdqa xmm2, xmm0;
			punpcklwd xmm0, xmm4;
			punpckhwd xmm2, xmm4;
			psrad xmm0, 10;
			psrad xmm2, 10;
			packssdw xmm0, xmm2;
			; 20.06.2016;
			packuswb xmm0, xmm7;
			punpcklbw xmm0, xmm7;

			movdqa xmm4, xmm1;
			pmullw xmm1, xmm5;
			pmulhw xmm4, xmm5;
			movdqa xmm2, xmm1;
			punpcklwd xmm1, xmm4;
			punpckhwd xmm2, xmm4;
			psrad xmm1, 10;
			psrad xmm2, 10;
			packssdw xmm1, xmm2;
			; 20.06.2016;
			packuswb xmm1, xmm7;
			punpcklbw xmm1, xmm7;

			; compress 8 word to 8 bytes;
			; saved result;
#      ifndef SET_UNALIGNED_FUNCT
			movdqa[ebx], xmm0;
			movdqa[ebx + 16], xmm1;
#      else
			movdqu[ebx], xmm0;
			movdqu[ebx + 16], xmm1;
#      endif

			add ebx, 32;
			sub ecx, 1;

			; 24.05.2016;
			jg cycle1;

			popad;
			emms;
		}
#    endif
		return;
	}
#  endif
#endif
}   // namespace libs::optim::s16bit::filter::sharp1
