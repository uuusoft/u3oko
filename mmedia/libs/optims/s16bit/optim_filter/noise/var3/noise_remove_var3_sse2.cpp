/**
\file       noise_remove_var3_sse2.cpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_filter
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "noise_remover3_x86.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::filter::noise::var3
{
void
sse2 (::libs::optim::io::MCallInfo& info)
{
#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#  else
  std::array< int, 2 >* bound_koeffs       = 0;
  std::array< int, 3 >* koeffs_remove      = 0;
  std::array< int, 1 >* bound_cond_koeffs  = 0;
  std::array< int, 1 >* koeffs_cond_remove = 0;

  get_params (info, bound_koeffs, koeffs_remove, bound_cond_koeffs, koeffs_cond_remove);

  std::int16_t exp_bounds[8] = {
    U3_CAST_INT16 ((*bound_koeffs)[0]),
    U3_CAST_INT16 ((*bound_koeffs)[1]),
    U3_CAST_INT16 ((*bound_cond_koeffs)[0]),
    U3_CAST_INT16 ((*koeffs_cond_remove)[0]),
    0,
    0,
    0,
    0
  };

  std::int16_t exp_koeffs[8] = {
    U3_CAST_INT16 ((*koeffs_remove)[0]),
    U3_CAST_INT16 ((*koeffs_remove)[1]),
    U3_CAST_INT16 ((*koeffs_remove)[2]),
    0,
    0,
    0,
    0,
    0
  };


  std::uint32_t loc_leak_stride = 0;

  calc_dest_dims (info.srcs_[0].stride_, info.srcs_[0].width_, loc_leak_stride, 8);


#    define XMM_REG_PREV_DATA xmm0
#    define XMM_REG_CUR_DATA xmm1
#    define XMM_REG_COMBINE_BOUND_KOEFF xmm6
#    define XMM_REG_COMBINE_REMOVENOISE_KOEFF xmm7
#    define XMM_REG_TEMP4 xmm5

#    define XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE xmm2
#    define XMM_REG_GENERATE_KOEFF_NOISE_REMOVE xmm3
#    define XMM_REG_ABS_DIFFERENSE xmm4

#    define XMM_REG_TEMP2 xmm2
#    define XMM_REG_TEMP3 xmm4


  const std::int16_t* cond_buf  = info.srcs_[1].buf ();
  std::int16_t*       prev_data = info.dsts_[0].buf ();
  std::int16_t*       cur_data  = info.srcs_[0].buf ();
  std::size_t         stride    = info.srcs_[0].stride_;
  std::size_t         width     = info.srcs_[0].width_;
  std::size_t         height    = info.srcs_[0].height_;


  __asm {
      pushad;

      ; загружаем коэффициенты в mmx регистры;
      lea eax, exp_bounds;
      movdqu XMM_REG_COMBINE_BOUND_KOEFF, [eax];

      lea eax, exp_koeffs;
      movdqu XMM_REG_COMBINE_REMOVENOISE_KOEFF, [eax];

      mov edi, prev_data;
      mov esi, cur_data;
      mov ebx, stride;

      mov ecx, height;
      mov edx, width;

    cycle1:
      mov eax, edx;

    cycle2:
      movdqa XMM_REG_PREV_DATA, [edi];
      movdqa XMM_REG_CUR_DATA, [esi];

      ; рассчет абсолютной разности между двумя буферами;
      movdqa XMM_REG_TEMP2, XMM_REG_PREV_DATA;
      movdqa XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_CUR_DATA;
      psubusw XMM_REG_TEMP2, XMM_REG_CUR_DATA;
      psubusw XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_PREV_DATA;
      por XMM_REG_TEMP2, XMM_REG_GENERATE_KOEFF_NOISE_REMOVE;
      movdqa XMM_REG_ABS_DIFFERENSE, XMM_REG_TEMP2;

      ; загружаем коэффициент слияния по умолчанию он положителен;
      pshuflw XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_COMBINE_REMOVENOISE_KOEFF, 0x00;<-(*koeffs_remove )[0]
      pshufd XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, 0x44;

      ; рассчет маски для выбора коэффициента для множения в зависимости от разности и коэффициента барьера;
      ; загружаем текущее порог отсечения для коэффциентов;
      movdqa XMM_REG_TEMP2, XMM_REG_ABS_DIFFERENSE;
      ; 30.05.2016;
      pshuflw XMM_REG_TEMP4, XMM_REG_COMBINE_BOUND_KOEFF, 0x00;<-(*bound_koeffs)[0]
      pshufd XMM_REG_TEMP4, XMM_REG_TEMP4, 0x44;
      pcmpgtw XMM_REG_TEMP2, XMM_REG_TEMP4;

      ; загружаем текущее смещение коэффиента слияния;
      pshuflw XMM_REG_TEMP4, XMM_REG_COMBINE_REMOVENOISE_KOEFF, 0x55;<-(*koeffs_remove )[1]
      pshufd XMM_REG_TEMP4, XMM_REG_TEMP4, 0x44;
      ; накладываем маску;
      pand XMM_REG_TEMP4, XMM_REG_TEMP2;
      paddsw XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_TEMP4;

      ; рассчет маски для выбора коэффициента для множения в зависимости от разности и коэффициента барьера;
      ; загружаем текущее порог отсечения для коэффциентов;
      movdqa XMM_REG_TEMP2, XMM_REG_ABS_DIFFERENSE;
      pshuflw XMM_REG_TEMP4, XMM_REG_COMBINE_BOUND_KOEFF, 0x55;<-(*bound_koeffs)[1]
      pshufd XMM_REG_TEMP4, XMM_REG_TEMP4, 0x44;
      pcmpgtw XMM_REG_TEMP2, XMM_REG_TEMP4;

      ; загружаем текущее смещение коэффиента слияния;
      pshuflw XMM_REG_TEMP4, XMM_REG_COMBINE_REMOVENOISE_KOEFF, 0xAA;<-(*koeffs_remove )[2]
      pshufd XMM_REG_TEMP4, XMM_REG_TEMP4, 0x44;
      ; накладываем маску;
      pand XMM_REG_TEMP4, XMM_REG_TEMP2;
      paddsw XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_TEMP4;      

      ; 30.05.2016 загружаем значение из буфера условий;
      push eax;
      mov eax, cond_buf;
      movdqa XMM_REG_TEMP4, [eax];

      ; смещаемся на следующую группу пикселей в буфере условий и сохраняем его;
      add eax, 16;
      mov cond_buf, eax;
      pop eax;

      ; загружаем значение границы для условий;
      pshuflw XMM_REG_TEMP2, XMM_REG_COMBINE_BOUND_KOEFF, 0xAA;<-(*bound_cond_koeffs)[0]
      pshufd XMM_REG_TEMP2, XMM_REG_TEMP2, 0x44;
      pcmpgtw XMM_REG_TEMP4, XMM_REG_TEMP2;

      pcmpeqw XMM_REG_TEMP2, XMM_REG_TEMP2; 0xFFFFFFFF
      pxor XMM_REG_TEMP2, XMM_REG_TEMP4; _mm_REG_TEMP2 = ~MM_REG_TEMP4

      ;pxor XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_GENERATE_KOEFF_NOISE_REMOVE;!!!!!!!!!!!!!!!!!!debug

      ; загружаем новые коэффициенты для тех значений, для которых значение условия больше чем граница;
      pshuflw XMM_REG_TEMP3, XMM_REG_COMBINE_BOUND_KOEFF, 0xFF;<-(*koeffs_cond_remove )[0]
      pshufd XMM_REG_TEMP3, XMM_REG_TEMP3, 0x44;
      pand XMM_REG_TEMP3, XMM_REG_TEMP4;
      pand XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_TEMP2;
      por XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_TEMP3;

      ; рассчет обратного коэффициента к вычисленным;
      ; генерация константы 128;
      pcmpeqw XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE; 0xFFFFFFFFFFFFFFFF;
      psrlw XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, 15;   0x0001000100010001;
      psllw XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, 7;    0x0080008000800080;
      psubsw XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_GENERATE_KOEFF_NOISE_REMOVE;

      ; умножение на выбранные коэффиенты;
      pmullw XMM_REG_PREV_DATA, XMM_REG_GENERATE_KOEFF_NOISE_REMOVE;
      pmullw XMM_REG_CUR_DATA, XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE;

      ; деление через сдвиг на 128;
      psraw XMM_REG_PREV_DATA, 7;
      psraw XMM_REG_CUR_DATA, 7;

      ; сложение;
      paddsw XMM_REG_PREV_DATA, XMM_REG_CUR_DATA;

      ; сохранение данных
      movdqa[edi], XMM_REG_PREV_DATA;
      movdqa[esi], XMM_REG_PREV_DATA;

      add esi, 16;
      add edi, 16;

      sub eax, 16;
      jg cycle2;

      add edi, ebx;
      add esi, ebx;

      mov eax, cond_buf;
      add eax, ebx;
      mov cond_buf, eax;

      sub ecx, 1;
      jg cycle1;

      popad;
      emms;

#    undef XMM_REG_PREV_DATA
#    undef XMM_REG_CUR_DATA
#    undef XMM_REG_COMBINE_BOUND_KOEFF
#    undef XMM_REG_COMBINE_REMOVENOISE_KOEFF
#    undef XMM_REG_ABS_DIFFERENSE
#    undef XMM_REG_TEMP4

#    undef XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE
#    undef XMM_REG_GENERATE_KOEFF_NOISE_REMOVE
  }
#  endif
  return;
}

}   // namespace libs::optim::s16bit::filter::noise::var3

#endif
