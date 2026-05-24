#pragma once
/**
\file       empty.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_codec_funcs
*/

namespace dlls::codecs::bitgen::lossy::pack_64s_to_70b_1::consts
{
const std::string   id_string             = "pack_64s_to_70b_1";
const std::uint32_t src_short_granularity = 64;
const std::uint32_t src_granularity       = sizeof (std::int16_t) * src_short_granularity;
const std::uint32_t dst_granularity       = sizeof (std::uint8_t) * 68;
}   // namespace dlls::codecs::bitgen::lossy::pack_64s_to_70b_1::consts


namespace dlls::codecs::bitgen::lossy::pack_64s_to_70b_1
{
class CObj : public IBitGen
{
  public:
  CObj ();
  virtual ~CObj ();

  protected:
  //  IBitGen overrides
  virtual void forward_int (
    const void*         src,
    const std::uint32_t count_byte_src,
    void*               dst,
    std::uint32_t&      count_byte_dst) override;

  virtual void backward_int (
    const void*         src,
    const std::uint32_t count_byte_src,
    void*               dst,
    std::uint32_t&      count_byte_dst) override;

  virtual std::uint32_t      get_granularity_int () const override;
  virtual const std::string& get_id_int () const override;
  virtual std::uint32_t      get_max_size_int (const std::uint32_t src_size) const override;

  private:
  const std::string id_string_;   //<
};
}   // namespace dlls::codecs::bitgen::lossy::pack_64s_to_70b_1
