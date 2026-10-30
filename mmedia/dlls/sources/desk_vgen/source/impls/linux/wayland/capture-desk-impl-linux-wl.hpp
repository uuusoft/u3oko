#pragma once
/**
\file       capture-desk-impl-linux-wl.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
*/
#if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)

#  include "PipeWireModule/PipeWireStream.hpp"
#  include "PortalModule/xdg-desktop-portal.hpp"
// #include "FFMPEGModule/FFmpegOutput.hpp"
// #include "GStreamerModule/GstOutput.hpp"
// #    include "c_common.h"
#  include <cstdio>
#  include <unistd.h>
#  include <signal.h>
#  include <sys/signalfd.h>
#  include <poll.h>

namespace dlls::sources::desk_vgen::impls::linux::wl
{
class CaptureDeskImplLinux : public ::dlls::sources::desk_vgen::ICaptureDeskImpl
{
  public:
  using share_info_type = std::optional< portal::SharedScreen >;

  CaptureDeskImplLinux ();
  virtual ~CaptureDeskImplLinux ();

  // EAI-REFACT
  auto thread_func_impl (std::uint32_t indx_thread) -> void;
  auto thread_postfunc_impl (std::uint32_t indx_thread) -> void;

  private:
  // ICaptureDeskImpl
  virtual auto get_buf_int (const syn::SourceImplInfo&, CaptureDeskInfo&) -> void override;

  share_info_type  share_info_;       //<
  std::thread      work_thread_;      //<
  std::atomic_bool stop_ { false };   //<
};
}   // namespace dlls::sources::desk_vgen::impls::linux::wl

#endif
