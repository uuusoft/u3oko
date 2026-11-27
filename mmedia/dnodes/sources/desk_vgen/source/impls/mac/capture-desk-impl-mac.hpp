#pragma once
/**
\file       capture-desk-impl-mac.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
*/

#ifdef U3_OS_MACX_DESKTOP
namespace dnodes::sources::desk_vgen::impls::mac
{
class CaptureDeskImplMac : public ::dnodes::sources::desk_vgen::ICaptureDeskImpl
{
  public:
  CaptureDeskImplMac ()          = default;
  virtual ~CaptureDeskImplMac () = default;

  private:
  // ICaptureDeskImpl
  virtual void get_buf_int (const syn::SourceImplInfo& props_info, CaptureDeskInfo& info) override;
};
}   // namespace dnodes::sources::desk_vgen::impls::mac
#endif
