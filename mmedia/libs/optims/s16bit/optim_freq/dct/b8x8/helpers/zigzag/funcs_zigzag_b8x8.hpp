#pragma once
/**
\file       funcs_zigzag_b8x8.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "mmedia/libs/optims/s16bit/optim_freq/dct/b8x8/consts/vals.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::helpers::zigzag::consts
{
// clang-format off

/// Таблица упорядочивания частотных коэффициентов по убыванию важности
U3_ALIGN_DEFAULT
const std::uint32_t forward_koeffs[b8x8::consts::count_elements_macroblock + 16] = {
   0,  1,  5,  6, 14, 15, 27, 28,  2,  4, 
   7, 13, 16, 26, 29, 42,  3,  8, 12, 17, 
  25, 30, 41, 43,  9, 11, 18, 24, 31, 40, 
  44, 53, 10, 19, 23, 32, 39, 45, 52, 54, 
  20, 22, 33, 38, 46, 51, 55, 60, 21, 34, 
  37, 47, 50, 56, 59, 61, 35, 36, 48, 49, 
  57, 58, 62, 63, 63, 63, 63, 63, 63, 63, 
  63, 63, /* extra entries for safety in decoder */
  63, 63, 63, 63, 63, 63, 63, 63
};
// clang-format on
}   // namespace libs::optim::s16bit::freq::dct::b8x8::helpers::zigzag::consts


namespace libs::optim::s16bit::freq::dct::b8x8::helpers::zigzag
{
/// функция производит прямое упорядочивание массива в зависимоти от степени важности частоты
inline void
forward (std::int16_t* buf)
{
  U3_ASSERT (buf);
  U3_ALIGN_DEFAULT std::int16_t temp[b8x8::consts::count_elements_macroblock];

  for (std::uint32_t indx = 0; indx < b8x8::consts::count_elements_macroblock; ++indx)
  {
    temp[indx] = buf[consts::forward_koeffs[indx]];
  }

  ::libs::helpers::mem::u3copy (temp, buf, b8x8::consts::count_elements_macroblock * sizeof (std::int16_t));
}

/// функция производит обратное нормальное упорядочивание массива по месту
inline void
backward (std::int16_t* buf)
{
  U3_ASSERT (buf);
  U3_ALIGN_DEFAULT std::int16_t temp[b8x8::consts::count_elements_macroblock];

  for (std::uint32_t indx = 0; indx < b8x8::consts::count_elements_macroblock; ++indx)
  {
    temp[consts::forward_koeffs[indx]] = buf[indx];
  }

  ::libs::helpers::mem::u3copy (temp, buf, b8x8::consts::count_elements_macroblock * sizeof (std::int16_t));
}
}   // namespace libs::optim::s16bit::freq::dct::b8x8::helpers::zigzag
