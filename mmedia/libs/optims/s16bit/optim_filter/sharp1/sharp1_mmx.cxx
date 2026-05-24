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
	void mmx ( ::libs::optim::io::MCallInfo& info )
	{
		U3_CHECK( check( info ), "failed" );

		if ( info.dsts_[0].height_ < 4 )
		{
			U3_ASSERTSIG( "failed" );
			return;
		}

		float temp_f1 = (8.0f + ( info.params_.consts_[0][0] + 2 ) );
		float temp_f2 = (5.0f + ( info.params_.consts_[0][0] + 2 ) );
		float temp_f3 = (1.0f / (float )( info.params_.consts_[0][0] + 2 ) ) * 1024.0f;

		// 26.03.2016 - corrected to std::int16_t conversion
		short array_div[4] =
		{
			(std::int16_t)( temp_f3), (std::int16_t)( temp_f3), (std::int16_t)( temp_f3), (std::int16_t)( temp_f3)
		};
		// 26.03.2016 - corrected to std::int16_t conversion
		short array_mull[4] =
		{
			(std::int16_t)( temp_f2 ), (std::int16_t)( temp_f1 ), (std::int16_t)( temp_f1 ), (std::int16_t)( temp_f2 )
		};

		int loc_number_byte = info.dsts_[0].stride_ * info.dsts_[0].height_;

		const void*	dest			= info.dsts_[0].buf();
		const int	stride_dest	= info.dsts_[0].stride_;

#      if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
		 U3_ASSERT_SIGNAL_I64;
		//U1UU_THROW_EXCEPTION("req intrinsic impl") );
#      else
		__asm
		{
			pushad;

			mov eax, stride_dest;
			mov ecx, loc_number_byte;

			sub ecx, eax;
			sub ecx, eax;
			shr ecx, 4;

			mov ebx, dest;
			add ebx, eax;

			lea edx, array_mull;
			movq mm6, [edx];

			lea edx, array_div;
			movq mm5, [edx];

			pxor mm7, mm7;

			cycle1:
			; mm0, mm1 - current 8 pixel;
			; mm7 - temporarely register[zero ? ];
			; mm6 - main mull koeff - 4 word;
			; mm2, mm3 - temporarely register;
			; mm4 - tempreraly register;
			; load main 8 bytes;
			movq mm0, qword ptr[ebx];
			movq mm1, qword ptr[ebx + 8];

			movq mm2, mm0;
			movq mm3, mm1;

			; mull 8 words to main koeff;
			pmullw mm0, mm6;
			pmullw mm1, mm6;

			; sub horizontal picter - ? ? ? ? ;
			movq mm4, mm2;
			psllq mm4, 16;
			psubsw mm0, mm4;
			movq mm4, mm2;
			psrlq mm4, 16;
			psubsw mm0, mm4;

			movq mm4, mm3;
			psllq mm4, 16;
			psubsw mm1, mm4;
			movq mm4, mm3;
			psrlq mm4, 16;
			psubsw mm1, mm4;

			; load upper 8 pixel;
			sub ebx, eax;

			movq mm2, qword ptr[ebx];
			movq mm3, qword ptr[ebx + 8];
			add ebx, eax;

			; add upper picter - ? ? ? ? ;
			movq mm4, mm2;
			psubsw mm0, mm4;
			psllq mm4, 16;
			psubsw mm0, mm4;
			movq mm4, mm2;
			psrlq mm4, 16;
			psubsw mm0, mm4;

			movq mm4, mm3;
			psubsw mm1, mm4;
			psllq mm4, 16;
			psubsw mm1, mm4;
			movq mm4, mm3;
			psrlq mm4, 16;
			psubsw mm1, mm4;

			; load lower 8 pixel;
			add ebx, eax;
			movq mm2, qword ptr[ebx];
			movq mm3, qword ptr[ebx + 8];
			sub ebx, eax;

			; add lower picter - ? ? ? ? ;
			movq mm4, mm2;
			psubsw mm0, mm4;
			psllq mm4, 16;
			psubsw mm0, mm4;
			movq mm4, mm2;
			psrlq mm4, 16;
			psubsw mm0, mm4;

			movq mm4, mm3;
			psubsw mm1, mm4;
			psllq mm4, 16;
			psubsw mm1, mm4;
			movq mm4, mm3;
			psrlq mm4, 16;
			psubsw mm1, mm4;

			; calculate average - div from mull and shift;
			movq mm4, mm0;
			pmullw mm0, mm5;
			pmulhw mm4, mm5;
			movq mm2, mm0;
			punpcklwd mm0, mm4;
			punpckhwd mm2, mm4;
			psrad mm0, 10;
			psrad mm2, 10;
			packssdw mm0, mm2;
			; 20.06.2016;
			packuswb mm0, mm7;
			punpcklbw mm0, mm7;

			movq mm4, mm1;
			pmullw mm1, mm5;
			pmulhw mm4, mm5;
			movq mm2, mm1;
			punpcklwd mm1, mm4;
			punpckhwd mm2, mm4;
			psrad mm1, 10;
			psrad mm2, 10;
			packssdw mm1, mm2;
			; 20.06.2016;
			packuswb mm1, mm7;
			punpcklbw mm1, mm7;

			; saved result;
			movq[ebx], mm0;
			movq[ebx + 8], mm1;

			add ebx, 16;
			sub ecx, 1;

			; 24.05.2016;
			jg cycle1;

			popad;
			emms;
		}
#      endif
		return;
	}
#    endif
#  endif
#endif
}   // namespace libs::optim::s16bit::filter::sharp1
