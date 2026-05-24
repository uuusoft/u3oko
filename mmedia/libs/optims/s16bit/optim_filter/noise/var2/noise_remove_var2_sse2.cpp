/**
\file       noise_remove_var2_sse2.cpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_filter
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "noise_remover2_x86.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::filter::noise::var2
{
void
sse2 (::libs::optim::io::MCallInfo& info)
{
#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#  else
  std::array< int, 2 >* bound_koeffs  = 0;
  std::array< int, 3 >* koeffs_remove = 0;

  get_params (info, bound_koeffs, koeffs_remove);

  std::int16_t loc_bound_koeffs[8] = {
    U3_CAST_INT16 ((*bound_koeffs)[0]),
    U3_CAST_INT16 ((*bound_koeffs)[1]),
    U3_CAST_INT16 ((*bound_koeffs)[0]),
    U3_CAST_INT16 ((*bound_koeffs)[1]),
    U3_CAST_INT16 ((*bound_koeffs)[0]),
    U3_CAST_INT16 ((*bound_koeffs)[1]),
    U3_CAST_INT16 ((*bound_koeffs)[0]),
    U3_CAST_INT16 ((*bound_koeffs)[1])
  };

  std::int16_t loc_koeffs_remove[8] = {
    U3_CAST_INT16 ((*koeffs_remove)[0]),
    U3_CAST_INT16 ((*koeffs_remove)[1]),
    U3_CAST_INT16 ((*koeffs_remove)[2]),
    U3_CAST_INT16 ((*koeffs_remove)[0]),
    U3_CAST_INT16 ((*koeffs_remove)[0]),
    U3_CAST_INT16 ((*koeffs_remove)[1]),
    U3_CAST_INT16 ((*koeffs_remove)[2]),
    U3_CAST_INT16 ((*koeffs_remove)[0])
  };


  std::uint32_t loc_leak_stride = (info.srcs_[0].width_ >> 3);

  if (info.srcs_[0].width_ & 0x7)
  {
    loc_leak_stride = loc_leak_stride + 1;
  }

  loc_leak_stride = (loc_leak_stride << 4);

  info.srcs_[0].stride_ = info.srcs_[0].stride_ - loc_leak_stride;
  info.srcs_[0].width_  = info.srcs_[0].width_ << 1;


#    define XMM_REG_DATA1_STRING xmm0
#    define XMM_REG_DATA2_STRING xmm1
#    define XMM_REG_COMBINE_BOUND_KOEFF xmm6
#    define XMM_REG_COMBINE_REMOVENOISE_KOEFF xmm7
#    define XMM_REG_ABS_DIFFERENSE xmm4
#    define XMM_REG_TEMP4 xmm5

#    define XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE xmm2
#    define XMM_REG_GENERATE_KOEFF_NOISE_REMOVE xmm3

#    define XMM_REG_TEMP2 xmm2

  std::int16_t* old_and_akk_source = info.dsts_[0].buf ();
  std::int16_t* new_source         = info.srcs_[0].buf ();
  std::uint32_t stride             = info.srcs_[0].stride_;
  std::uint32_t width              = info.srcs_[0].width_;
  std::uint32_t height             = info.srcs_[0].height_;


  __asm {
      pushad;

      ; загружаем коэффициенты в mmx регистры
      lea eax, loc_bound_koeffs;
      movdqu XMM_REG_COMBINE_BOUND_KOEFF, [eax];

      lea eax, loc_koeffs_remove;
      movdqu XMM_REG_COMBINE_REMOVENOISE_KOEFF, [eax];

      mov edi, old_and_akk_source;
      mov esi, new_source;
      mov ebx, stride;

      mov ecx, height;
      mov edx, width;


    cycle1:
      mov eax, edx;

    cycle2:
      movdqa XMM_REG_DATA1_STRING, [edi];
      movdqa XMM_REG_DATA2_STRING, [esi];

      ; рассчет абсолютной разности между двумя буферами
      movdqa XMM_REG_TEMP2, XMM_REG_DATA1_STRING;
      movdqa XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_DATA2_STRING;
      psubusw XMM_REG_TEMP2, XMM_REG_DATA2_STRING;
      psubusw XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_DATA1_STRING;
      por XMM_REG_TEMP2, XMM_REG_GENERATE_KOEFF_NOISE_REMOVE;
      movdqa XMM_REG_ABS_DIFFERENSE, XMM_REG_TEMP2;


      ; загружаем коэффициент слияния по умолчанию он положителен
      movdqa XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_COMBINE_REMOVENOISE_KOEFF;
      pshuflw XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, 0x00;
      pshufhw XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, 0x00;


      ; рассчет маски для выбора коэффициента для множения в зависимости от разности и коэффициента барьера
      ; загружаем текущее порог отсечения для коэффциентов
      movdqa XMM_REG_TEMP2, XMM_REG_ABS_DIFFERENSE;
      movdqa XMM_REG_TEMP4, XMM_REG_COMBINE_BOUND_KOEFF;
      pshuflw XMM_REG_TEMP4, XMM_REG_TEMP4, 0x00;
      pshufhw XMM_REG_TEMP4, XMM_REG_TEMP4, 0x00;
      pcmpgtw XMM_REG_TEMP2, XMM_REG_TEMP4;

      ; загружаем текущее смещение коэффиента слияния
      movdqa XMM_REG_TEMP4, XMM_REG_COMBINE_REMOVENOISE_KOEFF;
      pshuflw XMM_REG_TEMP4, XMM_REG_TEMP4, 0x55;
      pshufhw XMM_REG_TEMP4, XMM_REG_TEMP4, 0x55;
      ; накладываем маску
      pand XMM_REG_TEMP4, XMM_REG_TEMP2;
      paddsw XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_TEMP4;

      ; рассчет маски для выбора коэффициента для множения в зависимости от разности и коэффициента барьера
      ; загружаем текущее порог отсечения для коэффциентов
      movdqa XMM_REG_TEMP2, XMM_REG_ABS_DIFFERENSE;
      movdqa XMM_REG_TEMP4, XMM_REG_COMBINE_BOUND_KOEFF;
      pshuflw XMM_REG_TEMP4, XMM_REG_TEMP4, 0x55;
      pshufhw XMM_REG_TEMP4, XMM_REG_TEMP4, 0x55;
      pcmpgtw XMM_REG_TEMP2, XMM_REG_TEMP4;

      ; загружаем текущее смещение коэффиента слияния
      movdqa XMM_REG_TEMP4, XMM_REG_COMBINE_REMOVENOISE_KOEFF;
      pshuflw XMM_REG_TEMP4, XMM_REG_TEMP4, 0xAA;
      pshufhw XMM_REG_TEMP4, XMM_REG_TEMP4, 0xAA;
      ; накладываем маску
      pand XMM_REG_TEMP4, XMM_REG_TEMP2;
      paddsw XMM_REG_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_TEMP4;

      ; рассчет обратного коэффициента
      ; генерация константы 128
      pcmpeqw XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE; 0xFFFFFFFFFFFFFFFF
      psrlw XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, 15; 0x0001000100010001
      psllw XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, 7; 0x0080008000800080
      psubsw XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, XMM_REG_GENERATE_KOEFF_NOISE_REMOVE;

      ; умножение на выбранные коэффиенты
      pmullw XMM_REG_DATA1_STRING, XMM_REG_GENERATE_KOEFF_NOISE_REMOVE;
      pmullw XMM_REG_DATA2_STRING, XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE;

      ; деление через сдвиг на 128
      psraw XMM_REG_DATA1_STRING, 7;
      psraw XMM_REG_DATA2_STRING, 7;

      ; сложение
      paddsw XMM_REG_DATA1_STRING, XMM_REG_DATA2_STRING;

      ; сохранение данных
      movdqa[edi], XMM_REG_DATA1_STRING;
      movdqa[esi], XMM_REG_DATA1_STRING;

      add esi, 16;
      add edi, 16;

      sub eax, 16;
      jg cycle2;

      add edi, ebx;
      add esi, ebx;

      sub ecx, 1;
      jg cycle1;

      popad;
      emms;
  }
#  endif

#  undef XMM_REG_DATA1_STRING
#  undef XMM_REG_DATA2_STRING
#  undef XMM_REG_COMBINE_BOUND_KOEFF
#  undef XMM_REG_COMBINE_REMOVENOISE_KOEFF
#  undef XMM_REG_ABS_DIFFERENSE
#  undef XMM_REG_TEMP4

#  undef XMM_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE
#  undef XMM_REG_GENERATE_KOEFF_NOISE_REMOVE
}

}   // namespace libs::optim::s16bit::filter::noise::var2

#endif
