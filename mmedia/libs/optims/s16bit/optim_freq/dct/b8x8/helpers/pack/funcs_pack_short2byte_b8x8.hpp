#pragma once
/**
\file       funcs_pack_short2byte_b8x8.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_freq
*/
#include "mmedia/libs/optims/s16bit/optim_freq/dct/b8x8/consts/vals.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::helpers::pack
{
inline void
forward64 (const std::int16_t* src, std::uint8_t* dst)
{
  /*
    производим собственно сжатие в 8 бит, MMX каждого элемента массива, чтобы более эффективно сживать в RLE
    суда по статистике диапозон чисел после перехода в частотную область лежит в пределах одного байта
    одновременно сохрананяем данный блок данных

    отдельно обрабытваем первые 3 элемента таблицы, их надо хранить с повышенной точностью
    соотвественно 12 10 10 бит на элемент
    */
  U3_ASSERT (src);
  U3_ASSERT (dst);

  int res1 = src[0];
  int res2 = src[1];
  int res3 = src[2];

  res1 = ((res1 << 20) & 0x7FF00000) | (res1 & 0x80000000);
  res2 = ((res2 << 10) & 0x0007FC00) | ((res2 >> 12) & 0x00080000);
  res3 = (res3 & 0x000001FF) | ((res3 >> 22) & 0x00000200);

  *U3_CAST_REINTERPRET< unsigned long* > (dst) = res1 | res2 | res3;

  for (std::size_t indx = 3; indx < b8x8::consts::count_elements_macroblock; ++indx)
  {
    *(dst + indx + 1) = src[indx] > 127 ? 127 : ((src[indx] < -128) ? -128 : src[indx]);
  }
}


inline void
backward64 (const std::uint8_t* src, std::int16_t* dst)
{
  unsigned long first = *U3_CAST_REINTERPRET< const unsigned long* > (src);

  dst[0] = ((first >> 20) & 0x000007FF);

  if (first & 0x80000000)
  {
    dst[0] = dst[0] | 0xF800;
  }

  dst[1] = ((first >> 10) & 0x000001FF);

  if ((first << 12) & 0x80000000)
  {
    dst[1] = dst[1] | 0xFE00;
  }

  dst[2] = (first & 0x000001FF);

  if ((first << 22) & 0x80000000)
  {
    dst[2] = dst[2] | 0xFE00;
  }

  for (std::size_t indx = 3; indx < b8x8::consts::count_elements_macroblock; ++indx)
  {
    dst[indx] = U3_CAST_REINTERPRET< const char* > (src)[indx + 1];
  }
}

}   // namespace libs::optim::s16bit::freq::dct::b8x8::helpers::pack
