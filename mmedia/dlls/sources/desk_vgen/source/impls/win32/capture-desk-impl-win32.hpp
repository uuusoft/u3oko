#pragma once
/**
\file       capture-desk-impl-win32.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_desk_vgen
*/

namespace dlls::sources::desk_vgen::impls::win32
{
class CaptureDeskImplWin32 final : public ::dlls::sources::desk_vgen::ICaptureDeskImpl
{
  public:
  CaptureDeskImplWin32 ()          = default;
  virtual ~CaptureDeskImplWin32 () = default;

  private:
  // ICaptureDeskImpl
  virtual void get_buf_int (const syn::SourceImplInfo& props_info, CaptureDeskInfo& info) override;
};
}   // namespace dlls::sources::desk_vgen::impls::win32
