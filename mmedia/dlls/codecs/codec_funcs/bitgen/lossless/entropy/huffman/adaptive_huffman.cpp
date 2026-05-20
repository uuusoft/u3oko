/**
\file       adaptive_huffman.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016

\project    u3_codec_funcs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../codec-funcs-includes_int.hpp"
#include "../../../codec-funcs-bitgen-includes.hpp"
#include "adaptive_huffman.hpp"

namespace dlls::codecs::bitgen::lossless::entropy::huffman
{
CObj::CObj () :
  id_string_ (huffman::consts::id_string),
  key_symbol_ (0)
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
  U3_ASSERT (0 == count_byte_dst);

  const std::uint8_t* usrc    = U3_CAST_CODECS< const std::uint8_t* > (src);
  std::uint8_t*       udst    = U3_CAST_CODECS< std::uint8_t* > (dst);
  std::uint8_t        counter = 0;

  for (std::uint32_t indx = 0; indx < count_byte_src; ++indx)
  {
    if (key_symbol_ == usrc[indx])
    {
      if (0 == counter)
      {
        udst[count_byte_dst] = key_symbol_;
        ++count_byte_dst;
      }

      if (255 == counter)
      {
        udst[count_byte_dst] = counter;
        ++count_byte_dst;

        udst[count_byte_dst] = key_symbol_;
        ++count_byte_dst;

        counter = 0;
      }

      ++counter;
    }
    else
    {
      if (counter)
      {
        udst[count_byte_dst] = counter;
        ++count_byte_dst;
        counter = 0;
      }

      udst[count_byte_dst] = usrc[indx];
      ++count_byte_dst;
    }
  }

  if (counter)
  {
    udst[count_byte_dst] = counter;
    ++count_byte_dst;
    counter = 0;
  }
}


void
CObj::backward_int (
  const void*         src,
  const std::uint32_t count_byte_src,
  void*               dst,
  std::uint32_t&      count_byte_dst)
{
  const std::uint8_t* usrc = U3_CAST_CODECS< const std::uint8_t* > (src);
  std::uint8_t*       udst = U3_CAST_CODECS< std::uint8_t* > (dst);

  for (std::uint32_t indx = 0; indx < count_byte_src; ++indx)
  {
    if (key_symbol_ == usrc[indx])
    {
      const std::uint8_t counter = usrc[indx + 1];
      U3_ASSERT (counter);

      std::fill (udst + count_byte_dst, udst + count_byte_dst + counter, key_symbol_);

      count_byte_dst += counter;
      ++indx;
    }
    else
    {
      udst[count_byte_dst] = usrc[indx];
      ++count_byte_dst;
    }
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
  const std::uint32_t base = (src_size / get_granularity_int ()) * consts::dst_granularity;
  return base + (base / 2) + 1;
}
}   // namespace dlls::codecs::bitgen::lossless::entropy::huffman
