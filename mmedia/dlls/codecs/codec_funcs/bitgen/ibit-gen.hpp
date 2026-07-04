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
  U3_ADD_POINTERS_TO_SELF (IBitGen)
  U3_ADD_DELETE_MOVE_COPY (IBitGen)

  IBitGen ()          = default;
  virtual ~IBitGen () = default;

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

  auto get_granularity () const -> std::uint32_t;
  auto get_id () const -> const std::string&;
  auto get_max_size (const std::uint32_t src_size) const -> std::uint32_t;

  private:
  //  IBitGen interface
  virtual auto forward_int (const void*, const std::uint32_t, void*, std::uint32_t&) -> void  = 0;
  virtual auto backward_int (const void*, const std::uint32_t, void*, std::uint32_t&) -> void = 0;
  virtual auto get_granularity_int () const -> std::uint32_t                                  = 0;
  virtual auto get_id_int () const -> const std::string&                                      = 0;
  virtual auto get_max_size_int (const std::uint32_t src_size) const -> std::uint32_t         = 0;
};
}   // namespace dlls::codecs::bitgen
