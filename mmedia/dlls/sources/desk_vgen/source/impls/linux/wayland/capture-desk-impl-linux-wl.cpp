/**
\file       capture-desk-impl-linux-wl.cpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
*/
#define U3_DBG_LOG_LEVEL_ENABLE
#include "../../../desk-vgen-includes_int.hpp"
#include "capture-desk-impl-linux-wl.hpp"
#include "mmedia/libs/utility/thread/generic-thread-func.hpp"

#if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)

namespace dlls::sources::desk_vgen::impls::linux::wl
{
CaptureDeskImplLinux::CaptureDeskImplLinux ()
{
  U3_CALL_TRACE_DBG;
  work_thread_ = std::move (
    std::thread {
      ::libs::utility::thread::generic_thread_func< CaptureDeskImplLinux >,
      libs::properties::vers::links::mids::mdata2log,
      this,
      0U });
}


CaptureDeskImplLinux::~CaptureDeskImplLinux ()
{
  U3_CALL_TRACE_DBG;
  stop_ = true;
  work_thread_.join ();
  share_info_.reset ();
}


// boilerplate for std::visit with lambdas
template< class... Ts >
struct overloaded : Ts... {
  using Ts::operator()...;
};

template< class... Ts >
overloaded (Ts...) -> overloaded< Ts... >;

auto
CaptureDeskImplLinux::thread_func_impl (std::uint32_t indx_thread) -> void
{
  U3_CALL_TRACE_DBG;
  int         c                  = 0;
  bool        withCursor         = false;
  char*       hardwareDevicePath = nullptr;
  const char* outputPath         = nullptr;
  const char* outputFormat       = nullptr;

#  if 0
static void
printUsage (const char* argv0)
{
  printf ("Usage: %s [-c] -f <output format> -o <output path> -d <hardware device path>\n", argv0);
  puts ("\tWhere <hardware device path> is a DRM render node like /dev/dri/renderD128");
  puts ("\tWhere <output format> and <output path> can be any string that is recognized by ffmpeg");
}

  while ((c = getopt (argc, argv, "co:f:d:")) != -1)
  {
    switch (c)
    {
    case 'c':
      withCursor = true;
      break;
    case 'o':
      outputPath = optarg;
      break;
    case 'f':
      outputFormat = optarg;
      break;
    case 'd':
      hardwareDevicePath = optarg;
      break;
    case '?':
      fprintf (stderr, "Unrecognized option: '-%c'\n", optopt);
      printUsage (argv[0]);
      return;
    }
  }

  if (!outputPath || !outputFormat)
  {
    fprintf (stderr, "Both output path and format must be specified\n");
    printUsage (argv[0]);
    return;
  }

  if (!hardwareDevicePath)
  {
    fprintf (stderr, "Missing hardware device path\n");
    printUsage (argv[0]);
    return;
  }
#  endif

  sigset_t procMask;
  sigemptyset (&procMask);
  sigaddset (&procMask, SIGINT);
  sigaddset (&procMask, SIGTERM);
  sigprocmask (SIG_BLOCK, &procMask, nullptr);
#  if 1
  int signalFd = signalfd (-1, &procMask, SFD_CLOEXEC);
  if (signalFd == -1)
  {
    U3_XLOG_ERROR ("creating signalfd failed");
    return;
  }
#  endif
  U3_XLOG_DEV ("skip screencapture_wayland_init");
  int   argc    = 2;
  char* argv[3] = {
    "uuusoft",
    "/dev/dri/renderD128",
    nullptr
  };

  pw::init (&argc, ::libs::utility::casts::reinterpret_cast_helper< char*** > (&argv));
  // gstreamer::init (argc, argv);

  try
  {
    auto cursorMode = withCursor ? CURSOR_MODE_EMBED : CURSOR_MODE_HIDDEN;
    // share_info_   = portal::requestPipeWireShare (cursorMode);
    if (!share_info_)
    {
      U3_XLOG_MARK ("User cancelled request");
      close (signalFd);
      return;
    }


    printf ("SharedScreen fd = %d, node = %u\n", share_info_.value ().pipeWireFd, share_info_.value ().pipeWireNode);
#  if 0
    {
      std::uint64_t cycle_counter = 0;
      auto          pwStream      = pw::PipeWireStream (share_info_.value (), true);
      U3_XLOG_DEV ("init ffmpge - skip");
#    if 0      
      // this must be declared after and therefore destroyed before pwStream, so that frame processing is stopped
      // and all references to frames from the stream are dropped before pwStream is destroyed.
      // std::unique_ptr< ffmpeg::FFmpegOutput > ffmpegOutput;

      while (!stop_)
      {
        ++cycle_counter;
        struct pollfd fds[2];
        U3_XLOG_DEV ("prepace call pwStream.getEventPollFd" + VTOLOG (cycle_counter));
        fds[0] = { pwStream.getEventPollFd (), POLLIN, 0 };
        // fds[1]  = { signalFd, POLLIN, 0 };
        U3_XLOG_DEV ("prepace call poll" + VTOLOG (cycle_counter));
        int res = poll (fds, 1, 1000);
        if (res == -1)
        {
          if (errno == EAGAIN || errno == EINTR)
          {
            continue;
          }
          U3_XLOG_ERROR ("poll failed");
          return;
        }
#      if 0
        if (fds[1].revents & POLLIN)
        {
          signalfd_siginfo siginfo;
          read (signalFd, &siginfo, sizeof (siginfo));
          if (siginfo.ssi_signo == SIGINT || siginfo.ssi_signo == SIGTERM)
          {
            stop_ = true;
          }
        }
#      endif
        U3_XLOG_DEV ("cycle" + VTOLOG (cycle_counter) + VTOLOG (res));
        if (!(fds[0].revents & POLLIN))
        {
          continue;
        }

        auto ev = pwStream.nextEvent ();
        if (ev)
        {
          // call lambda function appropriate for the type of *ev
          std::visit (
            overloaded {
              [&] (pw::event::Connected& e) {
                U3_XLOG_DEV ("get connected - skip");
                // auto builder = ffmpeg::FFmpegOutput::Builder (e.dimensions, e.format, e.isDmaBuf);
                // builder
                //   .withScaling (common::Rect { 1920U, 1080U })
                //   .withHWDevice (hardwareDevicePath)
                //   .withOutputFormat (outputFormat)
                //   .withOutputPath (outputPath);
                // ffmpegOutput = std::make_unique< ffmpeg::FFmpegOutput > (builder.build ());
              },
              [&] (pw::event::Disconnected&) {
                U3_XLOG_DEV ("get disconnected");
                stop_ = true;
              },
              [&] (pw::event::MemoryFrameReceived& e) {
                U3_XLOG_DEV ("get MemoryFrameReceived - skip");
                // auto avFrame = ffmpeg::wrapInAVFrame (std::move (e.frame));
                // ffmpegOutput->pushFrame (ffmpeg::AVFrame_Heap (avFrame));
              },
              [&] (pw::event::DmaBufFrameReceived& e) {
                U3_XLOG_DEV ("get DmaBufFrameReceived - skip");
                // auto avFrame = ffmpeg::wrapInAVFrame (std::move (e.frame));
                // ffmpegOutput->pushFrame (ffmpeg::AVFrame_Heap (avFrame));
              } },
            *ev);
        }
      }
#    endif
    }
#  endif
    U3_XLOG_DEV ("skip  screencapture_wayland_deinit");
    pw::deinit ();
    // gstreamer::deinit ();

    close (signalFd);
  }
  catch (const std::exception& excpt)
  {
    close (signalFd);
    U3_XLOG_ERROR (excpt.what ());
  }
}


auto
CaptureDeskImplLinux::thread_postfunc_impl (std::uint32_t indx_thread) -> void
{
  U3_CALL_TRACE_DBG;
}


void
CaptureDeskImplLinux::get_buf_int (
  const syn::SourceImplInfo& props_info,
  CaptureDeskInfo&           info)
{
  return;
  if (!share_info_)
  {
    return;
  }

#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  XSetErrorHandler (error_handler);

  xlib_display_type display (XOpenDisplay (":0"));
  // Display* display = XOpenDisplay (":0");
  ::libs::utility::checks::throw_ifn (display, "XOpenDisplay");
  Window root = DefaultRootWindow (*display);
  ::libs::utility::checks::throw_ifn (root, "DefaultRootWindow");

  XWindowAttributes attrs;   // = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  memset (&attrs, 0, sizeof (attrs));
  ::libs::utility::checks::throw_ifn (XGetWindowAttributes (*display, root, &attrs), "XGetWindowAttributes");
  U3_LOG_DATA_DBG (VTOLOG (attrs.width) + VTOLOG (attrs.height) + VTOLOG (attrs.border_width) + VTOLOG (attrs.x) + VTOLOG (attrs.y) + VTOLOG (attrs.depth));
  U3_LOG_DATA_DBG (PTR_TOLOG (attrs.visual) + VTOLOG (attrs.c_class) + VTOLOG (attrs.bit_gravity) + VTOLOG (attrs.win_gravity) + VTOLOG (attrs.backing_store) + VTOLOG (attrs.map_state));
  // InputOnly
  // IsUnmapped
#    ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  int     x, y;          /* location of window */
  int     width, height; /* width and height of window */
  int     border_width;  /* border width of window */
  int     depth;         /* depth of window */
  Visual* visual;        /* the associated visual structure */
  Window  root;          /* root of screen containing window */
#      if defined(__cplusplus) || defined(c_plusplus)
  int c_class; /* C++ InputOutput, InputOnly*/
#      else
  int class; /* InputOutput, InputOnly*/
#      endif
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
#    endif
  ::libs::utility::checks::throw_ifn (attrs.width >= 0 && attrs.height >= 0 && attrs.border_width >= 0, VTOLOG (attrs.width) + VTOLOG (attrs.height) + VTOLOG (attrs.border_width));
  // xlib_image_type img (XGetImage (*display, root, 0, 0, attrs.width, attrs.height, AllPlanes, XYPixmap));
  // xlib_image_type img (XGetImage (*display, root, 0, 0, attrs.width, attrs.height, AllPlanes, ZPixmap));
  xlib_image_type img (XGetImage (*display, root, 0, 0, attrs.width, attrs.height, attrs.depth, XYPixmap));
  // XImage* img = XGetImage (*display, root, 0, 0, attrs.width, attrs.height, AllPlanes, XYPixmap);
  ::libs::utility::checks::throw_ifn (img, "XGetImage");
  const auto bitspx         = (*img)->depth;
  const auto bytespx        = (bitspx >> 3);
  const auto aligned_width  = ::libs::utility::mem::align_value (attrs.width, 64, true);
  const auto aligned_stride = ::libs::utility::mem::align_value (aligned_width * bytespx, 64, true);

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

  info.rgb_buf_->set_size (info.size_dest_data_);
  // XDestroyImage (img);
  // XCloseDisplay (display);
#  endif
}
}   // namespace dlls::sources::desk_vgen::impls::linux::wl

#endif
