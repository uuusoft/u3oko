/**
\file       gradient1_sse2.cxx
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/
#include "gradient1.hpp"

// old shit
namespace libs::optim::s16bit::gen::gradient1
{
#if 0
#  if defined(U3_CPU_X86)
#    ifndef SET_UNALIGNED_FUNCT
void
sse2 (
#    else
void
udest_sse2 (
#    endif
  ::libs::optim::io::MCallInfo& info)
{
  U3_CHECK (check (info));

  // calculate base and dx, dy
  short dx = U3_CAST_INT16 ((128 * info.params_.consts_[0][1]) / info.dsts_[0].width_);
  short dy = U3_CAST_INT16 ((128 * info.params_.consts_[0][2]) / info.dsts_[0].height_);

  const std::int16_t loc_array_dx[8] = {
    U3_CAST_INT16 (8 * dx),
    U3_CAST_INT16 (8 * dx),
    U3_CAST_INT16 (8 * dx),
    U3_CAST_INT16 (8 * dx),
    U3_CAST_INT16 (8 * dx),
    U3_CAST_INT16 (8 * dx),
    U3_CAST_INT16 (8 * dx),
    U3_CAST_INT16 (8 * dx)
  };

  const std::int16_t loc_array_dy[8] = {
    dy, dy, dy, dy, dy, dy, dy, dy
  };

  const std::int16_t loc_array_beg[8] = {
    info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0]
  };

  const std::int16_t loc_array_dx_beg[8] = {
    U3_CAST_INT16 (0 * dx),
    U3_CAST_INT16 (1 * dx),
    U3_CAST_INT16 (2 * dx),
    U3_CAST_INT16 (3 * dx),
    U3_CAST_INT16 (4 * dx),
    U3_CAST_INT16 (5 * dx),
    U3_CAST_INT16 (6 * dx),
    U3_CAST_INT16 (7 * dx)
  };

  std::size_t loc_leak_stride = 0;
  calc_dest_dims (info.dsts_[0].stride_, info.dsts_[0].width_, loc_leak_stride, 8);

  const void*       dest           = info.dsts_[0].buf ();
  const std::size_t stride_dest    = info.dsts_[0].stride_;
  const std::size_t width_element  = info.dsts_[0].width_;
  const std::size_t height_element = info.dsts_[0].height_;

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
    __asm
		{
			; xmm0 - result;
			; xmm1 - begin dx offset for all;
			; xmm2 - begin offest for current string;
			; xmm3 - begin offset for all array;
			; xmm4 - current offset dx * 128;
			; xmm5 - current offset dy * 128;
			; xmm6 - dx array;
			; xmm7 - dy array;

			pushad;

			lea edi, loc_array_dx_beg;
			movdqu xmm1, [edi];

			lea edi, loc_array_beg;
			movdqu xmm3, [edi];
			movdqu xmm2, xmm3;

			pxor xmm4, xmm4;
			pxor xmm5, xmm5;

			lea edi, loc_array_dx;
			movdqu xmm6, [edi];

			lea edi, loc_array_dy;
			movdqu xmm7, [edi];

			mov edi, dest;
			mov ebx, stride_dest;
			mov ecx, height_element;

			cycle1:

			mov eax, width_element;

			pxor xmm4, xmm4;

			cycle2:

			paddsw xmm4, xmm6;
#      ifndef SET_UNALIGNED_FUNCT
			movdqa xmm0, xmm4;
#      else
			movdqu xmm0, xmm4;
#      endif
			paddsw xmm0, xmm1;
			psraw xmm0, 7;
			paddsw xmm0, xmm2;
#      ifndef SET_UNALIGNED_FUNCT
			movdqa[edi], xmm0;
#      else
			movdqu[edi], xmm0;
#      endif

			add edi, 16;

			sub eax, 16;
			jg cycle2;

			add edi, ebx;

			paddsw xmm5, xmm7;
#      ifndef SET_UNALIGNED_FUNCT
			movdqa xmm2, xmm5;
#      else
			movdqu xmm2, xmm5;
#      endif
			psraw xmm2, 7;
			paddsw xmm2, xmm3;

			sub ecx, 1;
			jg cycle1;

			popad;
			emms;
		}
#    endif
  return;
}
#  endif
#endif
}   // namespace libs::optim::s16bit::gen::gradient1
