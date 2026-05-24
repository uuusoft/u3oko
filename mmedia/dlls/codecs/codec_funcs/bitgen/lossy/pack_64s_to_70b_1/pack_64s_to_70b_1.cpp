/**
\file       pack_64s_to_70b_1.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_codec_funcs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../codec-funcs-includes_int.hpp"
#include "../../codec-funcs-bitgen-includes.hpp"

namespace dlls::codecs::bitgen::lossy::pack_64s_to_70b_1
{
CObj::CObj () :
  id_string_ (consts::id_string)
{
}


CObj::~CObj ()
{
}


void
CObj::forward_int (
  const void*         src,
  const std::uint32_t count_byte_src,
  void*               dst,
  std::uint32_t&      count_byte_dst)
{
  U3_CHECK (count_byte_src >= 4, "source too small");
  const std::int16_t* ssrc = U3_CAST_CODECS< const std::int16_t* > (src);
  char*               udst = U3_CAST_CODECS< char* > (dst);

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

    res1 = ((res1 << 20) & 0x7FF00000) | (res1 & 0x80000000);
    res2 = ((res2 << 10) & 0x0007FC00) | ((res2 >> 12) & 0x00080000);
    res3 = (res3 & 0x000001FF) | ((res3 >> 22) & 0x00000200);

    *U3_CAST_CODECS< int* > (udst) = res1 | res2 | res3;

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
  const char*   usrc = U3_CAST_CODECS< const char* > (src);
  std::int16_t* sdst = U3_CAST_CODECS< std::int16_t* > (dst);

  for (std::uint32_t bindx = 0; bindx < count_byte_src / consts::dst_granularity; ++bindx)
  {
    const std::int32_t first = *U3_CAST_CODECS< const std::int32_t* > (usrc);

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
}   // namespace dlls::codecs::bitgen::lossy::pack_64s_to_70b_1
