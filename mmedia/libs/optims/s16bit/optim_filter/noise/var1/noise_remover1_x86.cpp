

/**
\file       noise_remover1_x86.cpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_filter
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "noise_remover1_x86.hpp"
//  old shit
namespace libs
{
namespace optim
{
namespace s16bit
{
namespace filter
{
namespace noise
{
namespace var1
{
#if 0
  bool remove_add_noise_alu ( ::libs::optim::io::MCallInfo& info )
  {
    U3_ASSERT_SIGNAL( "failed" );
    return false;
#  if 0
    for (uint32_t indx_y = 0; indx_y < info.height_; ++indx_y)
    {
      std::int16_t *beg_old_and_akk_source_string = r1einterpret_cast<short *>(rei1nterpret_cast<std::uint8_t*>( info.old_and_akk_source_ )+ indx_y * info.stride_ );
      std::int16_t *beg_new_source_string = re1interpret_cast<short *>(rei1nterpret_cast<std::uint8_t*>( info.new_source_ )+ indx_y * info.stride_ );

      for (uint32_t indx_x = 0; indx_x < info.width_; ++indx_x )
      {
        std::int16_t loc_res = beg_old_and_akk_source_string[indx_x] - beg_new_source_string[indx_x];
        loc_res = loc_res < 0 ? -loc_res : loc_res;

        std::int16_t temp_koeff = ( loc_res < info.bound_koeff_ ) ? info.koeff_below_ : info.koeff_above_;
        std::int16_t temp_inv_koeff = 128 - temp_koeff;

        beg_old_and_akk_source_string[indx_x] =
          s1tatic_cast<short>( ( ( temp_koeff * beg_old_and_akk_source_string[indx_x] ) >> 7) + ( ( temp_inv_koeff * beg_new_source_string[indx_x] ) >> 7) );

        ::libs::helpers::utils::check_bound<short> (beg_old_and_akk_source_string[indx_x], 0, 255 );

        beg_new_source_string[indx_x] = beg_old_and_akk_source_string[indx_x];
      }
    }

    return true;
#  endif
  }

  bool mmx ( ::libs::optim::io::MCallInfo& info )
  {
    U3_ASSERT_SIGNAL( "failed" );
    return false;
#  if 0
    const std::int16_t loc_array_bound_koeff[4] =
    {
      info.bound_koeff_, info.bound_koeff_,
      info.bound_koeff_, info.bound_koeff_
    };
    const std::int16_t loc_array_koeff_remove_noise1[4] =
    {
      info.koeff_below_, info.koeff_below_,
      info.koeff_below_, info.koeff_below_
    };
    const std::int16_t loc_array_koeff_remove_noise2[4] =
    {
      info.koeff_above_, info.koeff_above_,
      info.koeff_above_, info.koeff_above_
    };

    U3_ASSERT ( info.old_and_akk_source_ );
    U3_ASSERT ( info.new_source_ );
    U3_ASSERT( 0 < info.stride_ );
    U3_ASSERT( 0 < info.width_ );
    U3_ASSERT( 0 < info.height_ );

#    if 1
    std::uint32_t loc_leak_stride = ( info.width_ >> 2 );
    if ( info.width_ & 0x3)
      loc_leak_stride = loc_leak_stride + 1;

    loc_leak_stride = ( loc_leak_stride << 3);

    info.stride_ = info.stride_ - loc_leak_stride;
    info.width_  = info.width_ << 1;
#    else
    int loc_leak_stride = 0;

    calc_dest_dims_source( stride_dest, stride_source, width_element, loc_leak_stride, 4 );
#    endif


    void*     old_and_akk_source = info.old_and_akk_source_;
    void*     new_source     = info.new_source_;
    std::uint32_t  stride       = info.stride_;
    std::uint32_t  width        = info.width_;
    std::uint32_t  height       = info.height_;

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
    U3_ASSERT_SIGNAL_I64;
    //U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
    __asm
    {
      pushad;

      ; загружаем коэффициенты в mmx регистры
      lea eax, loc_array_bound_koeff;
      movq mm5, [eax];

      lea eax, loc_array_koeff_remove_noise1;
      movq mm6, [eax];

      lea eax, loc_array_koeff_remove_noise2;
      movq mm7, [eax];

      mov edi, old_and_akk_source;
      mov esi, new_source;
      mov ebx, stride;

      mov ecx, height;
      mov edx, width;

      ; генерация константы 128;
      pcmpeqw mm4, mm4; mm4 = 0xFFFFFFFFFFFFFFFF
      psrlw mm4, 15;   mm4 = 0x0001000100010001
      psllw mm4, 7;    mm4 = 0x0080008000800080

  cycle1:
      mov eax, edx;

      cycle2:
      movq mm0, [edi];
      movq mm1, [esi];

      ; рассчет абсолютной разности между двумя буферами;
      movq mm2, mm0;
      movq mm3, mm1;
      psubusw mm2, mm1;
      psubusw mm3, mm0;
      por mm2, mm3;

      ; рассчет маски для выбора коэффициента для множения в зависимости от разности и коэффициента барьера;
      pcmpgtw mm2, mm5;

      ; рассчет инверсной маски;
      pcmpeqw mm3, mm3; mm3 = 0xFFFFFFFFFFFFFFFF
      pxor mm3, mm2;

      ; выбор коэффициента для множения в зависимости от разности и коэффициента барьера;
      pand mm2, mm7;
      pand mm3, mm6;
      por mm2, mm3;

      ; рассчет обратного коэффициента;
      ; pcmpeqw mm3, mm3; mm3 = 0xFFFFFFFFFFFFFFFF;
      ; psrlw mm3, 15;   mm3 = 0x0001000100010001;
      ; psllw mm3, 7;    mm3 = 0x0080008000800080;
      movq mm3, mm4;
      psubsw mm3, mm2;

      ; умножение на выбранные коэффиенты;
      pmullw mm0, mm2;
      pmullw mm1, mm3;

      ; деление через сдвиг на 128;
      psraw mm0, 7;
      psraw mm1, 7;

      ; сложение
      paddsw mm0, mm1;

      ; сохранение данных
      movq[edi], mm0;
      movq[esi], mm0;

      add esi, 8;
      add edi, 8;

      sub eax, 8;
      jg cycle2;

      add edi, ebx;
      add esi, ebx;

      sub ecx, 1;
      jg cycle1;

      popad;
      emms;
    }
#    endif
    return true;
#  endif
  }

  bool sse1 ( ::libs::optim::io::MCallInfo& info )
  {
    return mmx ( info );
  }

  bool sse2 ( ::libs::optim::io::MCallInfo& info )
  {
    U3_ASSERT_SIGNAL( "failed" );
    return false;
#  if 0

    const std::int16_t loc_array_bound_koeff[8] =
    {
      info.bound_koeff_, info.bound_koeff_, info.bound_koeff_, info.bound_koeff_,
      info.bound_koeff_, info.bound_koeff_, info.bound_koeff_, info.bound_koeff_
    };

    const std::int16_t loc_array_koeff_remove_noise1[8] =
    {
      info.koeff_below_, info.koeff_below_, info.koeff_below_, info.koeff_below_,
      info.koeff_below_, info.koeff_below_, info.koeff_below_, info.koeff_below_
    };

    const std::int16_t loc_array_koeff_remove_noise2[8] =
    {
      info.koeff_above_, info.koeff_above_, info.koeff_above_, info.koeff_above_,
      info.koeff_above_, info.koeff_above_, info.koeff_above_, info.koeff_above_
    };

    U3_ASSERT ( info.old_and_akk_source_ );
    U3_ASSERT ( info.new_source_ );
    U3_ASSERT( 0 < info.stride_ );
    U3_ASSERT( 0 < info.width_ );
    U3_ASSERT( 0 < info.height_ );
    U3_ASSERT( ::libs::helpers::mem::check_align16_ptr ( info.old_and_akk_source_ ) );
    U3_ASSERT( ::libs::helpers::mem::check_align16_ptr ( info.new_source_ ) );
    U3_ASSERT( ::libs::helpers::mem::check_align16 ( info.stride_ ) );

#    if 1
    std::uint32_t loc_leak_stride = ( info.width_ >> 3);
    if ( info.width_ & 0x7)
      loc_leak_stride = loc_leak_stride + 1;

    loc_leak_stride = ( loc_leak_stride << 4 );

    info.stride_ = info.stride_ - loc_leak_stride;
    info.width_  = info.width_ << 1;
#    else
    int loc_leak_stride = 0;

    calc_dest_dims_source( stride_dest, stride_source, width_element, loc_leak_stride, 8 );
#    endif

    void*     old_and_akk_source = info.old_and_akk_source_;
    void*     new_source     = info.new_source_;
    std::uint32_t  stride       = info.stride_;
    std::uint32_t  width        = info.width_;
    std::uint32_t  height       = info.height_;

    __asm
    {
      pushad;

      ; загружаем коэффициенты в mmx регистры
      lea eax, loc_array_bound_koeff;
      movdqu xmm5, [eax];

      lea eax, loc_array_koeff_remove_noise1;
      movdqu xmm6, [eax];

      lea eax, loc_array_koeff_remove_noise2;
      movdqu xmm7, [eax];

      mov edi, old_and_akk_source;
      mov esi, new_source;
      mov ebx, stride;

      mov ecx, height;
      mov edx, width;

      ; генерация константы 128;
      pcmpeqw xmm4, xmm4; xmm4 = 0xFFFFFFFFFFFFFFFF
      psrlw xmm4, 15;    xmm4 = 0x0001000100010001
      psllw xmm4, 7;     xmm4 = 0x0080008000800080

  cycle1:
      mov eax, edx;

      cycle2:
      movdqa xmm0, [edi];
      movdqa xmm1, [esi];

      ; рассчет абсолютной разности между двумя буферами;
      movdqa xmm2, xmm0;
      movdqa xmm3, xmm1;
      psubusw xmm2, xmm1;
      psubusw xmm3, xmm0;
      por xmm2, xmm3;

      ; рассчет маски для выбора коэффициента для множения в зависимости от разности и коэффициента барьера;
      pcmpgtw xmm2, xmm5;

      ; рассчет инверсной маски
      pcmpeqw xmm3, xmm3; xmm3 = 0xFFFFFFFFFFFFFFFF
      pxor xmm3, xmm2;

      ; выбор коэффициента для множения в зависимости от разности и коэффициента барьера;
      pand xmm2, xmm7;
      pand xmm3, xmm6;
      por xmm2, xmm3;

      ; рассчет обратного коэффициента;
      movdqa xmm3, xmm4;
      psubsw xmm3, xmm2;

      ; умножение на выбранные коэффиенты;
      pmullw xmm0, xmm2;
      pmullw xmm1, xmm3;

      ; деление через сдвиг на 128
      psraw xmm0, 7;
      psraw xmm1, 7;

      ; сложение
      paddsw xmm0, xmm1;

      ; сохранение данных
      movdqa[edi], xmm0;
      movdqa[esi], xmm0;

      add esi, 16;
      add edi, 16;

      sub eax, 16;
      jg cycle2;

      add edi, ebx;
      add esi, ebx;

      sub ecx, 1;
      jg cycle1;

      popad;
    }
    return true;
#  endif
  }
#endif
}   // namespace var1
}   // namespace noise
}   // namespace filter
}   // namespace s16bit
}   // namespace optim
}   // namespace libs
