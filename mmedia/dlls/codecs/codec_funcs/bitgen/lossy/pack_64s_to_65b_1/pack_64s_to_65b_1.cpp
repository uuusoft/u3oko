/**
\file       pack_64s_to_65b_1.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_codec_funcs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../codec-funcs-includes_int.hpp"
#include "../../codec-funcs-bitgen-includes.hpp"

// EAI-REFACT
/// Макрос для формирования маски из заданного количества бит
#define INT_FILL_BITS32(mcount) \
  (~((~(::libs::helpers::casts::static_cast_helper< std::uint32_t > (1) << (mcount))) + 1))

/// Макрос для перемещения в заданную позицию бита знака
#define INT_MOVE_SIGN2BIT(val, sindx) \
  ((val & (::libs::helpers::casts::static_cast_helper< std::uint32_t > (1) << 31)) >> (31 - (sindx)))

/// Макрос для сжатия в заданное количество бит целого со знаком, проверка выхода за дипазон не производится
#define INT_COMPRESS32(val, icount) \
  ((val & INT_FILL_BITS32 (icount - 1)) | INT_MOVE_SIGN2BIT (val, icount - 1))

namespace dlls::codecs::bitgen::lossy::pack_64s_to_65b_1
{
void
CObj::forward_int (
  const void*         src,
  const std::uint32_t count_byte_src,
  void*               dst,
  std::uint32_t&      count_byte_dst)
{
  U3_CHECK (count_byte_src >= 4, "source too small");

  const auto* ssrc = ::libs::helpers::casts::reinterpret_cast_helper< const std::int16_t* > (src);
  auto*       udst = ::libs::helpers::casts::reinterpret_cast_helper< char* > (dst);

  for (std::uint32_t bindx = 0; bindx < count_byte_src / consts::src_granularity; ++bindx)
  {
    // производим собственно сжатие в 8 бит, MMX каждого элемента массива, чтобы более эффективно сживать в RLE
    // суда по статистике диапазон чисел после перехода в частотную область лежит в пределах одного байта
    // одновременно сохрананяем данный блок данных
    //
    // отдельно обрабытваем первые 3 элемента таблицы, их надо хранить с повышенной точностью
    // соответственно 12 10 10 бит на элемент
    int res1 = ssrc[0];
    int res2 = ssrc[1];
    int res3 = ssrc[2];

#if 1
    res1 = INT_COMPRESS32 (res1, 12) << 20;
    res2 = INT_COMPRESS32 (res2, 10) << 10;
    res3 = INT_COMPRESS32 (res3, 10) << 0;
#else
    res1 = ((res1 << 20) & 0x7FF00000) | ((res1 & 0x80000000) >> 0);
    res2 = ((res2 << 10) & 0x0007FC00) | ((res2 & 0x80000000) >> 12);
    res3 = (res3 & 0x000001FF) | ((res3 & 0x80000000) >> 22);
#endif

    *::libs::helpers::casts::reinterpret_cast_helper< int* > (udst) = res1 | res2 | res3;

    count_byte_dst += sizeof (int);

    for (std::uint32_t indx = 3; indx < consts::src_short_granularity; ++indx)
    {
      *(udst + indx + 1) = ssrc[indx] > 127 ? 127 : ((ssrc[indx] < -128) ? -128 : ssrc[indx]);
      ++count_byte_dst;
    }

    ssrc += consts::src_short_granularity;
    udst += consts::dst_granularity;
  }
}

void
CObj::backward_int (
  const void*         src,
  const std::uint32_t count_byte_src,
  void*               dst,
  std::uint32_t&      count_byte_dst)
{
  const auto* usrc = ::libs::helpers::casts::reinterpret_cast_helper< const char* > (src);
  auto*       sdst = ::libs::helpers::casts::reinterpret_cast_helper< std::int16_t* > (dst);

  for (std::uint32_t bindx = 0; bindx < count_byte_src / consts::dst_granularity; ++bindx)
  {
    const auto first = *::libs::helpers::casts::reinterpret_cast_helper< const std::int32_t* > (usrc);

    sdst[0] = ((first >> 20) & 0x000007FF);
    count_byte_dst += sizeof (std::int16_t);

    if (first & 0x80000000)
    {
      sdst[0] = sdst[0] | 0xF800;
    }

    sdst[1] = ((first >> 10) & 0x000001FF);
    count_byte_dst += sizeof (std::int16_t);

    if ((first << 12) & 0x80000000)
    {
      sdst[1] = sdst[1] | 0xFE00;
    }

    sdst[2] = (first & 0x000001FF);
    count_byte_dst += sizeof (std::int16_t);

    if ((first << 22) & 0x80000000)
    {
      sdst[2] = sdst[2] | 0xFE00;
    }

    for (std::uint32_t indx = 3; indx < consts::src_short_granularity; ++indx)
    {
      sdst[indx] = usrc[indx + 1];
      count_byte_dst += sizeof (std::int16_t);
    }

    usrc += consts::dst_granularity;
    sdst += consts::src_short_granularity;
  }
}

std::uint32_t
CObj::get_granularity_int () const
{
  return consts::src_granularity;
}

const std::string&
CObj::get_id_int () const
{
  return id_string_;
}

std::uint32_t
CObj::get_max_size_int (const std::uint32_t src_size) const
{
  return (src_size / get_granularity_int ()) * consts::dst_granularity;
}
}   // namespace dlls::codecs::bitgen::lossy::pack_64s_to_65b_1
