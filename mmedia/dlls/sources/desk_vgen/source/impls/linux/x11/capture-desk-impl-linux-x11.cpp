/**
\file       capture-desk-impl-linux-x11.cpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_desk_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../desk-vgen-includes_int.hpp"
#include "capture-desk-impl-linux-x11.hpp"

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
// #if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
#  include <X11/Xlib.h>
#  include <X11/Xutil.h>

namespace dlls::sources::desk_vgen::impls::linux::x11
{
static std::int32_t
error_handler (Display* d, XErrorEvent* e)
{
  U3_XLOG_ERROR ("failed xwindow funtion " + VTOLOG (e->error_code));
  return e->error_code;
}


void
CaptureDeskImplLinux::get_buf_int (
  const syn::SourceImplInfo& props_info,
  CaptureDeskInfo&           info)
{
  XSetErrorHandler (error_handler);

  xlib_display_type display (XOpenDisplay (":0"));
  // Display* display = XOpenDisplay (":0");
  U3_CHECK (display, "XOpenDisplay");
  Window root = DefaultRootWindow (*display);
  U3_CHECK (root, "DefaultRootWindow");

  XWindowAttributes attrs;   // = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  memset (&attrs, 0, sizeof (attrs));
  U3_CHECK (XGetWindowAttributes (*display, root, &attrs), "XGetWindowAttributes");
  U3_LOG_DATA_DBG (VTOLOG (attrs.width) + VTOLOG (attrs.height) + VTOLOG (attrs.border_width) + VTOLOG (attrs.x) + VTOLOG (attrs.y) + VTOLOG (attrs.depth));
  U3_LOG_DATA_DBG (PTR_TOLOG (attrs.visual) + VTOLOG (attrs.c_class) + VTOLOG (attrs.bit_gravity) + VTOLOG (attrs.win_gravity) + VTOLOG (attrs.backing_store) + VTOLOG (attrs.map_state));
  // InputOnly
  // IsUnmapped
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  int     x, y;          /* location of window */
  int     width, height; /* width and height of window */
  int     border_width;  /* border width of window */
  int     depth;         /* depth of window */
  Visual* visual;        /* the associated visual structure */
  Window  root;          /* root of screen containing window */
#    if defined(__cplusplus) || defined(c_plusplus)
  int c_class; /* C++ InputOutput, InputOnly*/
#    else
  int class; /* InputOutput, InputOnly*/
#    endif
  int           bit_gravity;           /* one of bit gravity values */
  int           win_gravity;           /* one of the window gravity values */
  int           backing_store;         /* NotUseful, WhenMapped, Always */
  unsigned long backing_planes;        /* planes to be preserved if possible */
  unsigned long backing_pixel;         /* value to be used when restoring planes */
  Bool          save_under;            /* boolean, should bits under be saved? */
  Colormap      colormap;              /* color map to be associated with window */
  Bool          map_installed;         /* boolean, is color map currently installed*/
  int           map_state;             /* IsUnmapped, IsUnviewable, IsViewable */
  long          all_event_masks;       /* set of events all people have interest in*/
  long          your_event_mask;       /* my event mask */
  long          do_not_propagate_mask; /* set of events that should not propagate */
  Bool          override_redirect;     /* boolean value for override-redirect */
  Screen*       screen;                /* back pointer to correct screen */
#  endif
  U3_CHECK (attrs.width >= 0 && attrs.height >= 0 && attrs.border_width >= 0, VTOLOG (attrs.width) + VTOLOG (attrs.height) + VTOLOG (attrs.border_width));
  // xlib_image_type img (XGetImage (*display, root, 0, 0, attrs.width, attrs.height, AllPlanes, XYPixmap));
  // xlib_image_type img (XGetImage (*display, root, 0, 0, attrs.width, attrs.height, AllPlanes, ZPixmap));
  xlib_image_type img (XGetImage (*display, root, 0, 0, attrs.width, attrs.height, attrs.depth, XYPixmap));
  // XImage* img = XGetImage (*display, root, 0, 0, attrs.width, attrs.height, AllPlanes, XYPixmap);
  U3_CHECK (img, "XGetImage");
  const auto bitspx         = (*img)->depth;
  const auto bytespx        = (bitspx >> 3);
  const auto aligned_width  = ::libs::helpers::mem::align_value (attrs.width, 64, true);
  const auto aligned_stride = ::libs::helpers::mem::align_value (aligned_width * bytespx, 64, true);

  info.width_dest_     = aligned_width;
  info.height_dest_    = attrs.height;
  info.stride_dest_    = aligned_stride;
  info.size_dest_data_ = info.stride_dest_ * info.height_dest_;

  info.rgb_buf_->resize (info.size_dest_data_);

  // U3_LOG_DATA_DEV (VTOLOG (attrs.x) + VTOLOG (attrs.y) + VTOLOG (attrs.depth) + VTOLOG (attrs.width) + VTOLOG (attrs.height));
  auto rgb_buf = info.rgb_buf_->get ();
  for (std::int32_t y = 0; y < attrs.height; ++y)
  {
    for (std::int32_t x = 0; x < attrs.width; ++x)
    {
      const auto pixel     = XGetPixel (*img, x, y);
      const auto pixel_off = y * info.stride_dest_ + x * bytespx;

      *(rgb_buf + pixel_off + 2) = (pixel & (*img)->red_mask) >> 16;
      *(rgb_buf + pixel_off + 1) = (pixel & (*img)->green_mask) >> 8;
      *(rgb_buf + pixel_off + 0) = (pixel & (*img)->blue_mask) >> 0;
    }
  }

  info.rgb_buf_->set_data_size (info.size_dest_data_);
  // XDestroyImage (img);
  // XCloseDisplay (display);
}
}   // namespace dlls::sources::desk_vgen::impls::linux::x11

#endif
