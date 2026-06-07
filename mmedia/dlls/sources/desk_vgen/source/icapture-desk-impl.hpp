#pragma once
/**
\file       icapture-desk-impl.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_desk_vgen
*/

namespace dlls::sources::desk_vgen
{
struct CaptureDeskInfo final {
  explicit CaptureDeskInfo (syn::IBlockMem::ptr& rgb_buf) :
    rgb_buf_ (rgb_buf),
    size_dest_data_ (0),
    width_dest_ (0),
    height_dest_ (0),
    stride_dest_ (0)
  {
  }

  syn::IBlockMem::ptr rgb_buf_;
  std::uint32_t       size_dest_data_;
  std::uint32_t       width_dest_;
  std::uint32_t       height_dest_;
  std::uint32_t       stride_dest_;
};

class ICaptureDeskImpl
{
  public:
  virtual ~ICaptureDeskImpl ()
  {
  }

  void
  get_buf (const syn::SourceImplInfo& props_info, CaptureDeskInfo& info)
  {
    get_buf_int (props_info, info);
  }

  protected:
  ICaptureDeskImpl ()
  {
  }

  private:
  // ICaptureDeskImpl
  virtual void get_buf_int (const syn::SourceImplInfo& props_info, CaptureDeskInfo& info) = 0;
};
}   // namespace dlls::sources::desk_vgen
