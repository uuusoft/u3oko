#pragma once
/**
\file       capture-desk-impl-linux-x11.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_desk_vgen
*/
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
// #if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
#  include "xlib-handlers-types.hpp"

namespace dlls::sources::desk_vgen::impls::linux::x11
{
class CaptureDeskImplLinux : public ::dlls::sources::desk_vgen::ICaptureDeskImpl
{
  public:
  CaptureDeskImplLinux ()          = default;
  virtual ~CaptureDeskImplLinux () = default;

  private:
  // ICaptureDeskImpl
  virtual void get_buf_int (const syn::SourceImplInfo& props_info, CaptureDeskInfo& info) override;

  xlib_display_type display_;   //<
  Screen*           screen_;    //<
  Window            root_;      //<
};
}   // namespace dlls::sources::desk_vgen::impls::linux::x11
#endif
