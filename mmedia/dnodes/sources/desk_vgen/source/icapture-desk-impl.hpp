#pragma once
/**
\file       icapture-desk-impl.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
*/

namespace dnodes::sources::desk_vgen
{
struct CaptureDeskInfo final {
  explicit CaptureDeskInfo (syn::IBlockMem::ptr& rgb_buf) :
    rgb_buf_ (rgb_buf)
  {
  }

  syn::IBlockMem::ptr rgb_buf_;
  std::uint32_t       size_dest_data_ { 0 };
  std::uint32_t       width_dest_ { 0 };
  std::uint32_t       height_dest_ { 0 };
  std::uint32_t       stride_dest_ { 0 };
};

class ICaptureDeskImpl
{
  public:
  virtual ~ICaptureDeskImpl () = default;

  auto
  get_buf (const syn::SourceImplInfo& props_info, CaptureDeskInfo& info) -> void
  {
    get_buf_int (props_info, info);
  }

  protected:
  ICaptureDeskImpl () = default;

  private:
  // ICaptureDeskImpl
  virtual auto get_buf_int (const syn::SourceImplInfo&, CaptureDeskInfo&) -> void = 0;
};
}   // namespace dnodes::sources::desk_vgen
