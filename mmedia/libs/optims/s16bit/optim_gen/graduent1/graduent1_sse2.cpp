/**
\file       gradient1_sse2.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "graduent1.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::gen::graduent1
{
void
sse2 (::libs::optim::io::MCallInfo& cinfo)
{
  check (cinfo);

#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM) || 1
  U3_ASSERT_TODO_OPTIM;
  alu (cinfo);

#    if 0
  std::uint8_t*         dest           = info.dsts_[0].ubuf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;
  const __m128i         mask_dest      = _mm_loadu_si128 (::libs::helpers::casts::reinterpret_cast_helper< const __m128i* > (mask_dest8));
  __m128i               consts         = _mm_loadu_si128 (::libs::helpers::casts::reinterpret_cast_helper< const __m128i* > (loc_array_const));
  consts                               = _mm_and_si128 (consts, mask_dest);

  for (std::uint32_t indy = 0; indy < height_element; ++indy)
  {
    for (std::uint32_t indx = 0; indx < sizeof (std::uint16_t) * width_element; indx += 16)
    {
#      ifdef SET_UNALIGNED_FUNCT
      __m128i xmm0 = _mm_loadu_si128 (::libs::helpers::casts::reinterpret_cast_helper< const __m128i* > (dest + indx));
#      else
      __m128i xmm0 = _mm_load_si128 (::libs::helpers::casts::reinterpret_cast_helper< const __m128i* > (dest + indx));
#      endif

      xmm0 = _mm_adds_epi16 (xmm0, consts);

#      ifdef SET_UNALIGNED_FUNCT
      _mm_store_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (dest + indx), xmm0);
#      else
      _mm_storeu_si128 (::libs::helpers::casts::reinterpret_cast_helper< __m128i* > (dest + indx), xmm0);
#      endif
    }
    //dest += width_element;
    dest += stride_dest;
  }
#    endif

#  else
  auto&               dst              = cinfo.dsts_[0];
  void*               image            = dst.buf ();
  const std::int16_t* input_grad_array = cinfo.params_.consts_[0];
  const std::int32_t  loc_leak_stride  = ((dst.width_ >> 3) + (dst.width_ & 0x7 ? 1 : 0)) << 4;
  const std::int32_t  stride_image     = dst.stride_ - loc_leak_stride;
  const std::int32_t  width_element    = dst.width_ << 1;
  const std::int32_t  height_element   = dst.height_;

  U3_ASSERT (::libs::helpers::mem::check_align16_ptr (image));
  U3_ASSERT (::libs::helpers::mem::check_align16 (dst.stride_));

  __asm {
      pushad;

      mov edi, image;
      mov edx, width_element;
      mov ecx, height_element;
      mov ebx, stride_image;
      mov esi, input_grad_array;

      movd xmm6, esi;
      pshufd xmm6, xmm6, 0;

      pxor xmm7, xmm7;

      cycle1:

      mov eax, width_element;
      ; mov eax, edx;

      cycle2:

      movdqa xmm0, [edi];

      ; копируем и ограничиваем до байта входные данные;
      packuswb xmm0, xmm7;
      punpcklbw xmm0, xmm7;
      ; простое дублирование во временные регистры;
      movdqa xmm1, xmm0;
      movdqa xmm2, xmm0;
      ; расширяем до двойного слова, чтобы без проблем использовать команду выделения двойного слова в общий регистр;
      punpcklwd xmm1, xmm7;
      punpckhwd xmm2, xmm7;
      ; получаем указатели на соотвествующие элементы в массиве путем умножения на 2 (т.к.массив shor) и сложения с базой;
      pslld xmm1, 1;
      pslld xmm2, 1;
      paddd xmm1, xmm6;
      paddd xmm2, xmm6;

      xor edx, edx;
      pxor xmm3, xmm3;

      ; для всех 8 значений полседовательно загружаем значение из памяти в регистр;
      movd esi, xmm1;
      mov dx, WORD ptr[esi];
      pinsrw xmm3, edx, 0;

      psrldq xmm1, 4;
      movd esi, xmm1;
      mov dx, WORD ptr[esi];
      pinsrw xmm3, edx, 2;

      psrldq xmm1, 4;
      movd esi, xmm1;
      mov dx, WORD ptr[esi];
      pinsrw xmm3, edx, 4;

      psrldq xmm1, 4;
      movd esi, xmm1;
      mov dx, WORD ptr[esi];
      pinsrw xmm3, edx, 6;

      pxor xmm4, xmm4;

      ; для всех 8 значений полседовательно загружаем значение из памяти в регистр;
      movd esi, xmm2;
      mov dx, WORD ptr[esi];
      pinsrw xmm4, edx, 0;

      psrldq xmm2, 4;
      movd esi, xmm2;
      mov dx, WORD ptr[esi];
      pinsrw xmm4, edx, 2;

      psrldq xmm2, 4;
      movd esi, xmm2;
      mov dx, WORD ptr[esi];
      pinsrw xmm4, edx, 4;

      psrldq xmm2, 4;
      movd esi, xmm2;
      mov dx, WORD ptr[esi];
      pinsrw xmm4, edx, 6;

      ; сохраняем полученные 8 значения обратно в массив;
      packssdw xmm3, xmm4;
      movdqa[edi], xmm3;

      add edi, 16;

      sub eax, 16;
      jg cycle2;

      add edi, ebx;

      sub ecx, 1;
      jg cycle1;

      popad;
      emms;
  }
#  endif
}
}   // namespace libs::optim::s16bit::gen::graduent1

#endif
