#pragma once
/**
\file       count_after_select_u8.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_codec_funcs
*/

namespace dlls::codecs::bitgen::lossless::entropy::rle::s16::consts
{
const std::string   id_string             = "rle_after_select_s16";
const std::uint32_t src_short_granularity = sizeof (std::int16_t);
const std::uint32_t src_granularity       = src_short_granularity;
const std::uint32_t dst_granularity       = src_granularity;
}   // namespace dlls::codecs::bitgen::lossless::entropy::rle::s16::consts


namespace dlls::codecs::bitgen::lossless::entropy::rle::s16
{
class CObj : public IBitGen
{
  public:
  //  ext types
  typedef CGenericObj< std::uint16_t > impl_type;

  CObj ()          = default;
  virtual ~CObj () = default;

  protected:
  virtual void               forward_int (const void* src, const std::uint32_t count_byte_src, void* dst, std::uint32_t& count_byte_dst) override;
  virtual void               backward_int (const void* src, const std::uint32_t count_byte_src, void* dst, std::uint32_t& count_byte_dst) override;
  virtual std::uint32_t      get_granularity_int () const override;
  virtual const std::string& get_id_int () const override;
  virtual std::uint32_t      get_max_size_int (const std::uint32_t src_size) const override;

  private:
  const std::string id_string_ = consts::id_string;   //<
  impl_type         impl_;                            //<
};
}   // namespace dlls::codecs::bitgen::lossless::entropy::rle::s16
