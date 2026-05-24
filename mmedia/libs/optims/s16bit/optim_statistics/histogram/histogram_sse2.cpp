/**
\file       histogram_sse2.cpp
\date       01.05.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_statistic
\brief      Функции для построения гистограммы частот вхождения байтов в изображение
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "histogram1.hpp"
#include "histogram1_int.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::statistics::histogram
{
void
sse2 (::libs::optim::io::MCallInfo& cinfo)
{
#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
  return alu (cinfo);
#  else
  int* out_freqs  = 0;
  int  size_freqs = 0;

  get_params (cinfo, out_freqs, size_freqs);

  std::size_t loc_leak_stride = (cinfo.srcs_[0].width_ >> 3);

  if (cinfo.srcs_[0].width_ & 0x7)
  {
    loc_leak_stride = loc_leak_stride + 1;
  }

  loc_leak_stride = (loc_leak_stride << 4);

  const void* source         = cinfo.srcs_[0].buf ();
  std::size_t stride_source  = cinfo.srcs_[0].stride_ - loc_leak_stride;
  std::size_t width_element  = cinfo.srcs_[0].width_;
  std::size_t height_element = cinfo.srcs_[0].height_;

  __asm {
      pushad;

      mov edi, source;
      mov edx, width_element;
      mov ecx, height_element;
      mov ebx, stride_source;
      mov esi, out_freqs;

      movd xmm6, esi;
      pshufd xmm6, xmm6, 0;

      pxor xmm7, xmm7;

      cycle1:

      mov eax, edx;

      cycle2:

      movdqa xmm0, [edi];

      packuswb xmm0, xmm7;
      punpcklbw xmm0, xmm7;

      movdqa xmm1, xmm0;
      movdqa xmm2, xmm0;

      punpcklwd xmm1, xmm7;
      punpckhwd xmm2, xmm7;

      pslld xmm1, 2;
      pslld xmm2, 2;

      paddd xmm1, xmm6;
      paddd xmm2, xmm6;

      movd esi, xmm1;
      add DWORD ptr[esi], 1;

      psrldq xmm1, 4;
      movd esi, xmm1;
      add DWORD ptr[esi], 1;

      psrldq xmm1, 4;
      movd esi, xmm1;
      add DWORD ptr[esi], 1;

      psrldq xmm1, 4;
      movd esi, xmm1;
      add DWORD ptr[esi], 1;

      movd esi, xmm2;
      add DWORD ptr[esi], 1;

      psrldq xmm2, 4;
      movd esi, xmm2;
      add DWORD ptr[esi], 1;

      psrldq xmm2, 4;
      movd esi, xmm2;
      add DWORD ptr[esi], 1;

      psrldq xmm2, 4;
      movd esi, xmm2;
      add DWORD ptr[esi], 1;

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
}   // namespace libs::optim::s16bit::statistics::histogram

#endif
