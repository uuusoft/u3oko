#pragma once
/**
\file       CQuant.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_freq
*/
#include "mmedia/libs/optims/s16bit/optim_freq/dct/b8x8/consts/vals.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::helpers::quant
{
class CQuant final
{
  public:
  CQuant ();

  ~CQuant ();

  void update (std::int32_t koeff);

  void forward (std::int16_t* buf) const;

  void backward (std::int16_t* buf) const;


  private:
  std::int32_t koeff_;                                                    //< коэффициент качества 1.100
  std::int32_t scale_koeff_;                                              //< коэффициент масштабирования таблицы на основе коэффициента качества
  std::int32_t quant_table_y_[b8x8::consts::count_elements_macroblock];   //< таблица квантования - текушая, формируется на основе опорной и коэффициента сжатия
};
}   // namespace libs::optim::s16bit::freq::dct::b8x8::helpers::quant
