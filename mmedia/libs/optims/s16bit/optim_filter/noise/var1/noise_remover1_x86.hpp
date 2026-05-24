#pragma once
/**
\file       noise_remover1_x86.hpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_filter

Формула преобразования

koeff_remove_noise1 = [0.0f...1.0f] * 128
koeff_remove_noise2 = [0.0f...1.0f] * 128
koeff_remove_noise1 > koeff_remove_noise2
bound_koeff = (0.0f...0.5f] * 128

diff = ABS( IN[x,y] - OUT[x,y] )
temp_koeff = diff > bound_koeff ? koeff_remove_noise2 : koeff_remove_noise1;

OUT[x,y] = (1.0f - temp_koeff ) * IN[x,y] + temp_koeff * OUT[x,y]
IN[x,y] = OUT[x,y]


Добавил второй набор функций для генерации эффекта ЛСД путем суммирования с переполнением, т.к.
данный набор отличается от предыдущего только осуствием порога и инверитрованием коэффициента

30.05.2016 добавлен третитий вариант, в нем дополнительно введен буфер условий, если текущее значение
в буфере условий больше некого предела, коэффициент выбирается специфический
*/

// old shit
namespace optim::s16bit::filter::noise::var1
{
#if 0
#  if 1

typedef ::libs::optim::io::MCallInfo ::libs::optim::io::MCallInfo;
#  else

struct ::libs::optim::io::MCallInfo {
  ::libs::optim::io::MCallInfo (
    void*        old_and_akk_source,
    void*        new_source,
    int          stride,
    int          width,
    int          height,
    std::int16_t bound_koeff,
    std::int16_t koeff_below,
    std::int16_t koeff_above) :

    old_and_akk_source_ (old_and_akk_source),
    new_source_ (new_source),
    stride_ (stride),
    width_ (width),
    height_ (height),
    bound_koeff_ (bound_koeff),
    koeff_below_ (koeff_below),
    koeff_above_ (koeff_above)
  {
  }

  bool
  check () const
  {
    return true;
  }

  void*        old_and_akk_source_;
  void*        new_source_;
  std::int32_t stride_;
  std::int32_t width_;
  std::int32_t height_;
  std::int16_t bound_koeff_;
  std::int16_t koeff_below_;
  std::int16_t koeff_above_;
};
#  endif

// typedef bool (*TNoiseRemoveFunct ) ( ::libs::optim::io::MCallInfo& info );

bool remove_add_noise_alu (::libs::optim::io::MCallInfo& info);
bool mmx (::libs::optim::io::MCallInfo& info);
bool sse1 (::libs::optim::io::MCallInfo& info);
bool sse2 (::libs::optim::io::MCallInfo& info);
#endif
}   // namespace optim::s16bit::filter::noise::var1
