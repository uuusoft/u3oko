#pragma once
/**
\file       capture-desk-impl-linux-wl.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_desk_vgen
*/
#if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)

// #  include "PipeWireModule/PipeWireStream.hpp"
#  if 0
#    include "PortalModule/xdg-desktop-portal.hpp"
#  endif
// #include "FFMPEGModule/FFmpegOutput.hpp"
// #include "GStreamerModule/GstOutput.hpp"
#  if 0
#    include "c_common.h"
#  endif
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
  CaptureDeskImplLinux ();
  virtual ~CaptureDeskImplLinux ();

  private:
  // ICaptureDeskImpl
  virtual void get_buf_int (const syn::SourceImplInfo& props_info, CaptureDeskInfo& info) override;

  void thread_func ();

#  if 0
  std::optional< portal::SharedScreen > share_info_;   //<
#  endif

  std::thread work_thread_;   //<
  // auto pwStream_ = pw::PipeWireStream(shareInfo.value(), true);
  //  xlib_display_type display_;   //<
  //  Screen*           screen_;    //<
  //  Window            root_;      //<
};
}   // namespace dlls::sources::desk_vgen::impls::linux::wl
#endif
