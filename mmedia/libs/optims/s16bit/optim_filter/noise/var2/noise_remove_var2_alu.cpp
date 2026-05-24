

/**
\file       noise_remove_var2_alu.cpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_filter
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "noise_remover2_x86.hpp"

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
namespace var2
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  std::array< int, 2 >* bound_koeffs  = 0;
  std::array< int, 3 >* koeffs_remove = 0;

  get_params (info, bound_koeffs, koeffs_remove);

#if 0
    std::int16_t loc_bound_koeffs[4] =
    {
      (*bound_koeffs)[0], (*bound_koeffs)[1],
      (*bound_koeffs)[0], (*bound_koeffs)[1]
    };

    std::int16_t loc_koeffs_remove[4] =
    {
      (*koeffs_remove )[0], (*koeffs_remove )[1],
      (*koeffs_remove )[2], (*koeffs_remove )[1]
    };
#endif

  std::uint32_t loc_leak_stride = (info.srcs_[0].width_ >> 2);

  if (info.srcs_[0].width_ & 0x3)
  {
    loc_leak_stride = loc_leak_stride + 1;
  }

  loc_leak_stride = (loc_leak_stride << 3);

  info.srcs_[0].stride_ = info.srcs_[0].stride_ - loc_leak_stride;
  info.srcs_[0].width_  = info.srcs_[0].width_ << 1;


  U3_ASSERT_SIGNAL ("failed");
  return;

#if 0
#  define _mm_REG_DATA1_STRING mm0
#  define _mm_REG_DATA2_STRING mm1
#  define _mm_REG_COMBINE_BOUND_KOEFF mm6
#  define _mm_REG_COMBINE_REMOVENOISE_KOEFF mm7
#  define _mm_REG_ABS_DIFFERENSE mm4
#  define _mm_REG_TEMP4 mm5

#  define _mm_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE mm2
#  define _mm_REG_GENERATE_KOEFF_NOISE_REMOVE mm3

#  define _mm_REG_TEMP2 mm2

    std::int16_t*      old_and_akk_source = info.dsts_[0].buf();
    std::int16_t*      new_source     = info.srcs_[0].buf();
    std::uint32_t  stride       = info.srcs_[0].stride_;
    std::uint32_t  width        = info.srcs_[0].width_;
    std::uint32_t  height       = info.srcs_[0].height_;

    __asm
    {
      pushad;

      ; загружаем коэффициенты в mmx регистры
      lea eax, loc_bound_koeffs;
      movq _mm_REG_COMBINE_BOUND_KOEFF, [eax];

      lea eax, loc_koeffs_remove;
      movq _mm_REG_COMBINE_REMOVENOISE_KOEFF, [eax];

      mov edi, old_and_akk_source;
      mov esi, new_source;
      mov ebx, stride;

      mov ecx, height;
      mov edx, width;

      cycle1:
      mov eax, edx;

      cycle2:
      movq _mm_REG_DATA1_STRING, [edi];
      movq _mm_REG_DATA2_STRING, [esi];

      ; рассчет абсолютной разности между двумя буферами
      movq _mm_REG_TEMP2, _mm_REG_DATA1_STRING;
      movq _mm_REG_GENERATE_KOEFF_NOISE_REMOVE, _mm_REG_DATA2_STRING;
      psubusw _mm_REG_TEMP2, _mm_REG_DATA2_STRING;
      psubusw _mm_REG_GENERATE_KOEFF_NOISE_REMOVE, _mm_REG_DATA1_STRING;
      por _mm_REG_TEMP2, _mm_REG_GENERATE_KOEFF_NOISE_REMOVE;
      movq _mm_REG_ABS_DIFFERENSE, _mm_REG_TEMP2;

      ; загружаем коэффициент слияния по умолчанию он положителен
      pshufw _mm_REG_GENERATE_KOEFF_NOISE_REMOVE, _mm_REG_COMBINE_REMOVENOISE_KOEFF, 0x00;

      ; рассчет маски для выбора коэффициента для множения в зависимости от разности и коэффициента барьера
      ; загружаем текущее порог отсечения для коэффциентов
      movq _mm_REG_TEMP2, _mm_REG_ABS_DIFFERENSE;
      ; 30.05.2016
      pshufw _mm_REG_TEMP4, _mm_REG_COMBINE_BOUND_KOEFF, 0x00;
      pcmpgtw _mm_REG_TEMP2, _mm_REG_TEMP4;


      ; загружаем текущее смещение коэффиента слияния
      pshufw _mm_REG_TEMP4, _mm_REG_COMBINE_REMOVENOISE_KOEFF, 0x55;
      ; накладываем маску
      pand _mm_REG_TEMP4, _mm_REG_TEMP2;
      paddsw _mm_REG_GENERATE_KOEFF_NOISE_REMOVE, _mm_REG_TEMP4;


      ; рассчет маски для выбора коэффициента для множения в зависимости от разности и коэффициента барьера
      ; загружаем текущее порог отсечения для коэффциентов
      movq _mm_REG_TEMP2, _mm_REG_ABS_DIFFERENSE;
      pshufw _mm_REG_TEMP4, _mm_REG_COMBINE_BOUND_KOEFF, 0x55;
      pcmpgtw _mm_REG_TEMP2, _mm_REG_TEMP4;

      ; загружаем текущее смещение коэффиента слияния
      pshufw _mm_REG_TEMP4, _mm_REG_COMBINE_REMOVENOISE_KOEFF, 0xAA;
      ; накладываем маску
      pand _mm_REG_TEMP4, _mm_REG_TEMP2;
      paddsw _mm_REG_GENERATE_KOEFF_NOISE_REMOVE, _mm_REG_TEMP4;


      ; рассчет обратного коэффициента к вычисленным
      ; генерация константы 128
      pcmpeqw _mm_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, _mm_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE; 0xFFFFFFFFFFFFFFFF
      psrlw _mm_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, 15;   0x0001000100010001
      psllw _mm_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, 7;    0x0080008000800080
      psubsw _mm_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE, _mm_REG_GENERATE_KOEFF_NOISE_REMOVE;

      ; умножение на выбранные коэффиенты
      pmullw _mm_REG_DATA1_STRING, _mm_REG_GENERATE_KOEFF_NOISE_REMOVE;
      pmullw _mm_REG_DATA2_STRING, _mm_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE;

      ; деление через сдвиг на 128
      psraw _mm_REG_DATA1_STRING, 7;
      psraw _mm_REG_DATA2_STRING, 7;

      ; сложение
      paddsw _mm_REG_DATA1_STRING, _mm_REG_DATA2_STRING;

      ; сохранение данных
      movq[edi], _mm_REG_DATA1_STRING;
      movq[esi], _mm_REG_DATA1_STRING;

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

#  undef _mm_REG_DATA1_STRING
#  undef _mm_REG_DATA2_STRING
#  undef _mm_REG_COMBINE_BOUND_KOEFF
#  undef _mm_REG_COMBINE_REMOVENOISE_KOEFF
#  undef _mm_REG_ABS_DIFFERENSE
#  undef _mm_REG_TEMP4

#  undef _mm_REG_REVESE_GENERATE_KOEFF_NOISE_REMOVE
#  undef _mm_REG_GENERATE_KOEFF_NOISE_REMOVE
#  undef XMM_REG_TEMP2
    }
    return true;
#endif
}

}   // namespace var2
}   // namespace noise
}   // namespace filter
}   // namespace s16bit
}   // namespace optim
}   // namespace libs
