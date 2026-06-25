#pragma once
/**
\file     hdc2rgb24_func.hpp
\brief    function for convert anybody hdc to rgb24, if needed buf relloc from ::base_funcs::mem::arealloc
\author   Erashov Anton erashov2026@proton.me
\date     26.07.2016
*/
#ifdef U3_OS_WIN32_DESKTOP

namespace dlls::sources::desk_vgen::impls::win32::helpers
{
struct Hdc2BmpCallInfo final {
  Hdc2BmpCallInfo (
    HDC                                  source_hdc,
    ::libs::helpers::mem::IBlockMem::ptr dest_buf,
    std::uint32_t                        __dest_bits,
    std::uint32_t*                       active_dest_buf,
    std::uint32_t*                       width_dest,
    std::uint32_t*                       height_dest,
    std::uint32_t*                       stride_dest,
    bool                                 inverse_vert) :

    source_hdc_ (source_hdc),
    dest_buf_ (dest_buf),
    dest_count_bits_ (__dest_bits),
    active_dest_buf_ (active_dest_buf),
    width_dest_ (width_dest),
    height_dest_ (height_dest),
    stride_dest_ (stride_dest),
    vinvert_ (inverse_vert)
  {
  }

  bool
  check () const
  {
    if (!source_hdc_ || !active_dest_buf_ || !stride_dest_)
    {
      U3_ASSERT_SIGNAL_NT ("failed");
      return false;
    }

    if ((dest_count_bits_ != 16) && (dest_count_bits_ != 24) && (dest_count_bits_ != 32))
    {
      U3_ASSERT_SIGNAL_NT ("failed");
      return false;
    }
    return true;
  }

  HDC                                  source_hdc_;
  ::libs::helpers::mem::IBlockMem::ptr dest_buf_;
  std::uint32_t                        dest_count_bits_;
  std::uint32_t*                       active_dest_buf_;
  std::uint32_t*                       width_dest_;
  std::uint32_t*                       height_dest_;
  std::uint32_t*                       stride_dest_;
  bool                                 vinvert_;
};

typedef bool (*convert_hdc2rgb_func_type) (Hdc2BmpCallInfo& info);

void hdc2buf_alu (Hdc2BmpCallInfo& info);
}   // namespace dlls::sources::desk_vgen::impls::win32::helpers
#endif
