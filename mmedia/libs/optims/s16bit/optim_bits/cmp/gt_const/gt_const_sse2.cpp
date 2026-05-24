/**
\file       gt_const_sse2.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_bits
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "gt_const.hpp"
#include "gt_const_int.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::bits::cmp::gt_const
{
void
sse2 (::libs::optim::io::MCallInfo& info)
{
#  if 1
  U3_ASSERT_TODO_OPTIM;
  return alu (info);
#  else
  const std::uint16_t* mask_dest8 = 0;
  std::int16_t         const1     = 0;
  std::int16_t         const2     = 0;

  get_params (info, mask_dest8, const1, const2);

  std::size_t number_sub_pixel_x = 0;
  std::size_t number_sub_pixel_y = 0;
  std::size_t leak_stride_dest   = 0;

  calc_source_dims (
    info.dsts_[0].stride_, info.dsts_[0].width_, info.dsts_[0].height_, 8, number_sub_pixel_x, number_sub_pixel_y, leak_stride_dest);

  U3_ASSERT (0 < number_sub_pixel_y);

#    ifndef SET_UNALIGNED_FUNCT
  U3_ASSERT (::libs::helpers::mem::check_align16_ptr (info.dsts_[0].buf ()));
  U3_ASSERT (::libs::helpers::mem::check_align16 (info.dsts_[0].stride_));
#    endif

  std::int16_t*          dest                    = info.dsts_[0].buf ();
  U3_ALIGN_DEFAULT const std::int16_t consts1[8] = { const1, const1, const1, const1, const1, const1, const1, const1 };
  U3_ALIGN_DEFAULT const std::int16_t consts2[8] = { const2, const2, const2, const2, const2, const2, const2, const2 };

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
    __asm
    {
      ; eax - leak_stride_source;
      ; ebx - cycle for col;
      ; ecx - cycle for row;
      ; edx - source;
      ; edi - leak_stride_dest;
      ; esi - dest;
      ; xmm0 - current string source;
      ; xmm1 - current string dest;
      ; xmm2 -;
      ; xmm3 -;
      ; xmm4 -;
      ; xmm5 - current cmp bound;
      ; xmm6 - mask source equal inv mm7;
      ; xmm7 - mask dest;

      pushad;

      lea eax, consts1;
      movdqu xmm5, [eax];

      lea eax, consts2;
      movdqu xmm4, [eax];

      mov eax, mask_dest8;
      movdqu xmm7, [eax];

      movdqa xmm6, xmm7;
      pcmpeqw xmm0, xmm0;
      pxor xmm6, xmm0;

      ; mov eax, leak_stride_source;
      mov edi, leak_stride_dest;
      mov ecx, number_sub_pixel_y;
      ; mov edx, source;
      mov esi, dest;

      cycle_row:
      mov ecx, number_sub_pixel_x;

      cycle_col:
      ; movdqa xmm0, [edx];

#      ifndef SET_UNALIGNED_FUNCT
      movdqa xmm1, [esi];
#      else
      movdqu xmm1, [esi];
#      endif
      movdqa xmm0, xmm1;

      pcmpgtw xmm0, xmm5;
      movdqa xmm2, xmm4;
      pand xmm0, xmm2;
      movdqa xmm2, xmm1;
      movdqa xmm2, xmm0;
      ; paddsw xmm2, xmm0;
      pand xmm2, xmm7;
      pand xmm1, xmm6;
      por xmm1, xmm2;

    // saved result
#      ifndef SET_UNALIGNED_FUNCT
      movdqa[esi], xmm1;
#      else
      movdqu[esi], xmm1;
#      endif

      //go to next
      ; add edx, 16;
      add esi, 16;

      sub ecx, 1;
      ; 24.05.2016;
      jg cycle_col;

      ; add edx, eax;
      add esi, edi;

      sub number_sub_pixel_y, 1;
      ; 24.05.2016;
      jg cycle_row;

      popad;
    }
#    endif
#  endif
}

}   // namespace libs::optim::s16bit::bits::cmp::gt_const

#endif
