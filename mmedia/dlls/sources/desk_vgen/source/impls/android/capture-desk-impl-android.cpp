/**
\file       capture-desk-impl-android.cpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_desk_vgen
*/
#include "../../desk-vgen-includes_int.hpp"
#include "capture-desk-impl-android.hpp"

#ifdef U3_OS_ANDROID

namespace dlls::sources::desk_vgen::impls::android
{
void
CaptureDeskImplAndroid::get_buf_int (const syn::SourceImplInfo& props_info, CaptureDeskInfo& info)
{
  U3_LOG_DATA_DEV ("CaptureDeskImplAndroid::get_buf_int");
  // void* bits = nullptr;
  // int   fd   = open ("/dev/graphics/fb0", O_RDWR);
  // U3_CHECK (fd >= 0, "open /dev/graphics/fb0");
  // close (fd);

#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  int   fd;
  void* bits;

  fd = open ("/dev/graphics/fb0", O_RDWR);
  if (fd < 0)
  {
    perror ("cannot open fb0");
    return -1;
  }

  if (ioctl (fd, FBIOGET_FSCREENINFO, &fi) < 0)
  {
    perror ("to get fb0 info");
    return -1;
  }

  if (ioctl (fd, FBIOGET_VSCREENINFO, &vi) < 0)
  {
    perror ("to get fb0 info");
    return -1;
  }

  // dumpinfo(&fi, &vi);

  bits = mmap (0, fi.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (bits == MAP_FAILED)
  {
    perror ("to mmap framebuf");
    return -1;
  }

  fb->version = sizeof (*fb);
  fb->width   = vi.xres;
  fb->height  = vi.yres;
  fb->stride  = fi.line_length / (vi.bits_per_pixel >> 3);
  fb->data    = bits;
  fb->format  = GGL_PIXEL_FORMAT_RGB_565;

  fb++;

  fb->version = sizeof (*fb);
  fb->width   = vi.xres;
  fb->height  = vi.yres;
  fb->stride  = fi.line_length / (vi.bits_per_pixel >> 3);
  fb->data    = (void*) (((unsigned) bits) + vi.yres * vi.xres * 2);
  fb->format  = GGL_PIXEL_FORMAT_RGB_565;

#  endif

#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  // int       size_dest_data = 0;
  // int       width_dest     = ::libs::utility::consts::iinvalid;
  // int       height_dest    = ::libs::utility::consts::iinvalid;
  // int       stride_dest    = 0;
  const std::int32_t dest_bits = 24;

  {
    const auto window = GetDesktopWindow ();
    RECT       window_rect;
    POINT      offset_pos = { 0, 0 };

    U3_CHECK (GetClientRect (window, &window_rect), "GetClientRect" + VTOLOG (GetLastError ()));

    switch (props_info.capture_props_->type_capture_)
    {
    case ::libs::events_base::props::videos::generic::driver::CatchRgns::cursor_area: {
      width_dest  = props_info.capture_props_->width_;
      height_dest = props_info.capture_props_->height_;

      U3_CHECK (GetPhysicalCursorPos (&offset_pos), "GetCursorPos" + VTOLOG (GetLastError ()));
      // U3_CHECK (PhysicalToLogicalPoint (window, &offset_pos), "PhysicalToLogicalPoint" + VTOLOG (GetLastError ()));
      // U3_CHECK (LogicalToPhysicalPointForPerMonitorDPI (window, &offset_pos), "PhysicalToLogicalPointForPerMonitorDPI" + VTOLOG (GetLastError ()));

      int loc_x = offset_pos.x;
      int loc_y = offset_pos.y;

      loc_x -= width_dest / 2;
      loc_y -= height_dest / 2;

      ::libs::utility::utils::check_bound (loc_x, 0, (window_rect.right - window_rect.left) - width_dest);
      ::libs::utility::utils::check_bound (loc_y, 0, (window_rect.bottom - window_rect.top) - height_dest);

      offset_pos.x = loc_x;
      offset_pos.y = loc_y;
      break;
    }
    case ::libs::events_base::props::videos::generic::driver::CatchRgns::hwnd:
    case ::libs::events_base::props::videos::generic::driver::CatchRgns::desktop:
    case ::libs::events_base::props::videos::generic::driver::CatchRgns::selection:
    default: {
      width_dest  = props_info.capture_props_->width_;
      height_dest = props_info.capture_props_->height_;
      break;
    }
    }

    ::dlls::sources::desk_vgen::impls::win32::helpers::window2rgb (
      window,
      rgb_buf,
      offset_pos.x,
      offset_pos.y,
      size_dest_data,
      width_dest,
      height_dest,
      stride_dest,
      dest_bits);
  }
#  endif
}
}   // namespace dlls::sources::desk_vgen::impls::android

#endif
