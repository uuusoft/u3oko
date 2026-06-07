#pragma once
/**
\file       capture-desk-impl-mac.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_desk_vgen
*/

#ifdef U3_OS_MACX_DESKTOP
namespace dlls::sources::desk_vgen::impls::mac
{
class CaptureDeskImplMac : public ::dlls::sources::desk_vgen::ICaptureDeskImpl
{
  public:
  CaptureDeskImplMac ()          = default;
  virtual ~CaptureDeskImplMac () = default;

  private:
  // ICaptureDeskImpl
  virtual void get_buf_int (const syn::SourceImplInfo& props_info, CaptureDeskInfo& info) override;
};
}   // namespace dlls::sources::desk_vgen::impls::mac
#endif
