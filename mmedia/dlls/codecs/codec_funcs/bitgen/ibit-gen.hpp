#pragma once
/**
\file       ibit-gen.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_codec_funcs
*/

namespace dlls::codecs::bitgen
{
class IBitGen
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IBitGen)

  IBitGen ()          = default;
  virtual ~IBitGen () = default;

  IBitGen (const IBitGen& src)                  = delete;
  const IBitGen& operator= (const IBitGen& src) = delete;

  void forward (
    const void*         src,
    const std::uint32_t count_byte_src,
    void*               dst,
    std::uint32_t&      count_byte_dst);

  void backward (
    const void*         src,
    const std::uint32_t count_byte_src,
    void*               dst,
    std::uint32_t&      count_byte_dst);

  std::uint32_t      get_granularity () const;
  const std::string& get_id () const;
  std::uint32_t      get_max_size (const std::uint32_t src_size) const;

  private:
  //  IBitGen interface
  virtual void forward_int (
    const void*         src,
    const std::uint32_t count_byte_src,
    void*               dst,
    std::uint32_t&      count_byte_dst) = 0;

  virtual void backward_int (
    const void*         src,
    const std::uint32_t count_byte_src,
    void*               dst,
    std::uint32_t&      count_byte_dst) = 0;

  virtual std::uint32_t      get_granularity_int () const                          = 0;
  virtual const std::string& get_id_int () const                                   = 0;
  virtual std::uint32_t      get_max_size_int (const std::uint32_t src_size) const = 0;
};
}   // namespace dlls::codecs::bitgen
