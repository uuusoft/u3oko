#pragma once
/**
\file       test_copy_xx_to_xx.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_codec_funcs
*/

namespace dlls::codecs::bitgen::lossless::test_copy_xx_to_xx::consts
{
const std::string id_string                   = "test_copy_xx_to_xx";
constexpr std::uint32_t src_short_granularity = 1;
constexpr std::uint32_t src_granularity       = src_short_granularity;
constexpr std::uint32_t dst_granularity       = src_granularity;
}   // namespace dlls::codecs::bitgen::lossless::test_copy_xx_to_xx::consts


namespace dlls::codecs::bitgen::lossless::test_copy_xx_to_xx
{
class CObj : public IBitGen
{
  public:
  CObj () :
    id_string_ (consts::id_string)
  {
  }

  virtual ~CObj ()
  {
  }

  protected:
  virtual void
  forward_int (
    const void*         src,
    const std::uint32_t count_byte_src,
    void*               dst,
    std::uint32_t&      count_byte_dst) override
  {
    count_byte_dst = count_byte_src;
    ::libs::helpers::mem::u3copy (src, dst, count_byte_src);
  }

  virtual void
  backward_int (
    const void*         src,
    const std::uint32_t count_byte_src,
    void*               dst,
    std::uint32_t&      count_byte_dst) override
  {
    forward_int (src, count_byte_src, dst, count_byte_dst);
  }

  virtual std::uint32_t
  get_granularity_int () const override
  {
    return consts::src_granularity;
  }

  virtual const std::string&
  get_id_int () const override
  {
    return id_string_;
  }

  virtual std::uint32_t
  get_max_size_int (const std::uint32_t src_size) const override
  {
    return (src_size / get_granularity_int ()) * consts::dst_granularity;
  }

  private:
  const std::string id_string_;   //<
};
}   // namespace dlls::codecs::bitgen::lossless::test_copy_xx_to_xx
