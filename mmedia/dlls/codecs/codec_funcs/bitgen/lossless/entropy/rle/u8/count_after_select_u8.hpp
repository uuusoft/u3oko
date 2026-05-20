#pragma once
/**
\file       count_after_select_u8.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017

\project    u3_codec_funcs
*/

namespace dlls::codecs::bitgen::lossless::entropy::rle::u8::consts
{
const std::string   id_string             = "rle_after_select_u8";
const std::uint32_t src_short_granularity = sizeof (std::uint8_t);
const std::uint32_t src_granularity       = src_short_granularity;
const std::uint32_t dst_granularity       = src_granularity;
}   // namespace dlls::codecs::bitgen::lossless::entropy::rle::u8::consts


namespace dlls::codecs::bitgen::lossless::entropy::rle::u8
{
class CObj : public IBitGen
{
  public:
  //  ext types
  typedef CGenericObj< std::uint8_t > impl_type;

  CObj ();
  virtual ~CObj ();

  protected:
  virtual void               forward_int (const void* src, const std::uint32_t count_byte_src, void* dst, std::uint32_t& count_byte_dst) override;
  virtual void               backward_int (const void* src, const std::uint32_t count_byte_src, void* dst, std::uint32_t& count_byte_dst) override;
  virtual std::uint32_t      get_granularity_int () const override;
  virtual const std::string& get_id_int () const override;
  virtual std::uint32_t      get_max_size_int (const std::uint32_t src_size) const override;

  private:
  const std::string id_string_;   //<
  impl_type         impl_;        //<
};
}   // namespace dlls::codecs::bitgen::lossless::entropy::rle::u8
