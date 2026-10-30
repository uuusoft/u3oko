/**
\file       ibit-gen.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
*/
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
  ::libs::utility::checks::throw_ifn (src, "null src");
  ::libs::utility::checks::throw_ifn (count_byte_src, "empty src");
  ::libs::utility::checks::throw_ifn (dst, "null dst");
  ::libs::utility::checks::throw_ifn (::libs::utility::mem::check_align< std::uint32_t > (count_byte_src, get_granularity ()), "src granularity unalign");

  count_byte_dst = 0;
  forward_int (src, count_byte_src, dst, count_byte_dst);
  ::libs::utility::checks::throw_if (count_byte_dst <= 0, "dst empty");
}


void
IBitGen::backward (
  const void*         src,
  const std::uint32_t count_byte_src,
  void*               dst,
  std::uint32_t&      count_byte_dst)
{
  ::libs::utility::checks::throw_ifn (src, "null src");
  ::libs::utility::checks::throw_ifn (count_byte_src, "empty src");
  ::libs::utility::checks::throw_ifn (dst, "null dst");

  count_byte_dst = 0;
  backward_int (src, count_byte_src, dst, count_byte_dst);
  ::libs::utility::checks::throw_if (count_byte_dst <= 0, "impl, dst empty");
}


auto
IBitGen::get_granularity () const -> std::uint32_t
{
  const std::uint32_t ret = get_granularity_int ();
  ::libs::utility::checks::throw_if (ret <= 0, "ret less or equal 0" + VTOLOG (ret));
  return ret;
}


auto
IBitGen::get_id () const -> const std::string&
{
  const std::string& ret = get_id_int ();
  ::libs::utility::checks::throw_if (ret.empty (), "empty string");
  ::libs::utility::checks::throw_if (ret.length () > ::libs::events_base::props::videos::generic::codec::consts::max_len_name_entropy_coder, "impl, length id bit gen too large");
  return ret;
}


auto
IBitGen::get_max_size (const std::uint32_t src_size) const -> std::uint32_t
{
  ::libs::utility::checks::throw_if (src_size <= 0, "size src less or equal 0: src_size");
  std::uint32_t ret = get_max_size_int (src_size);
  ::libs::utility::checks::throw_if (ret <= 0, "size less or equal 0" + VTOLOG (ret));
  return ret;
}
}   // namespace dlls::codecs::bitgen
