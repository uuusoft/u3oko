/**
\file       count_after_select_u8.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_codec_funcs
*/
#include "../../../../../codec-funcs-includes_int.hpp"
#include "../../../../codec-funcs-bitgen-includes.hpp"

namespace dlls::codecs::bitgen::lossless::entropy::rle::s16
{
void
CObj::forward_int (
  const void*         src,
  const std::uint32_t count_byte_src,
  void*               dst,
  std::uint32_t&      count_byte_dst)
{
  impl_.forward (
    src,
    count_byte_src,
    dst,
    count_byte_dst);
}


void
CObj::backward_int (
  const void*         src,
  const std::uint32_t count_byte_src,
  void*               dst,
  std::uint32_t&      count_byte_dst)
{
  impl_.backward (
    src,
    count_byte_src,
    dst,
    count_byte_dst);
}


auto
CObj::get_granularity_int () const -> std::uint32_t
{
  return consts::src_granularity;
}


auto
CObj::get_id_int () const -> const std::string&
{
  return id_string_;
}


auto
CObj::get_max_size_int (const std::uint32_t src_size) const -> std::uint32_t
{
  const std::uint32_t base = (src_size / get_granularity_int ()) * consts::dst_granularity;
  return base + (base / 2) + 1;
}
}   // namespace dlls::codecs::bitgen::lossless::entropy::rle::s16
