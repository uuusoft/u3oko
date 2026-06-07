/**
\file       ibit-gen.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_codec_funcs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../codec-funcs-includes_int.hpp"
#include "ibit-gen.hpp"

namespace dlls::codecs::bitgen
{
void
IBitGen::forward (
  const void*         src,
  const std::uint32_t count_byte_src,
  void*               dst,
  std::uint32_t&      count_byte_dst)
{
  U3_CHECK (src, "null src");
  U3_CHECK (count_byte_src, "empty src");
  U3_CHECK (dst, "null dst");
  U3_CHECK (::libs::helpers::mem::check_align< std::uint32_t > (count_byte_src, get_granularity ()), "src granularity unalign");

  count_byte_dst = 0;
  forward_int (src, count_byte_src, dst, count_byte_dst);
  U3_CHECK (count_byte_dst > 0, "dst empty");
}


void
IBitGen::backward (
  const void*         src,
  const std::uint32_t count_byte_src,
  void*               dst,
  std::uint32_t&      count_byte_dst)
{
  U3_CHECK (src, "null src");
  U3_CHECK (count_byte_src, "empty src");
  U3_CHECK (dst, "null dst");

  count_byte_dst = 0;
  backward_int (src, count_byte_src, dst, count_byte_dst);
  U3_CHECK (count_byte_dst > 0, "impl, dst empty");
}


std::uint32_t
IBitGen::get_granularity () const
{
  const std::uint32_t ret = get_granularity_int ();
  U3_CHECK (ret > 0, "ret less or equal 0" + VTOLOG (ret));
  return ret;
}


const std::string&
IBitGen::get_id () const
{
  const std::string& ret = get_id_int ();
  U3_CHECK (!ret.empty (), "empty string");
  U3_CHECK (ret.length () <= ::libs::ievents::props::videos::generic::codec::consts::max_len_name_entropy_coder, "impl, length id bit gen too large");
  return ret;
}


std::uint32_t
IBitGen::get_max_size (const std::uint32_t src_size) const
{
  U3_CHECK (src_size > 0, "size src less or equal 0: src_size");
  std::uint32_t ret = get_max_size_int (src_size);
  U3_CHECK (ret > 0, "size less or equal 0" + VTOLOG (ret));
  return ret;
}
}   // namespace dlls::codecs::bitgen
