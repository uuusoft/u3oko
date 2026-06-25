/**
\file       capture-desk-impl-win32.cpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_desk_vgen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../desk-vgen-includes_int.hpp"
#include "helpers/hdc2rgb24_func.hpp"
#include "helpers/window2rgb.hpp"
#include "capture-desk-impl-win32.hpp"

#ifdef U3_OS_WIN32_DESKTOP

namespace dlls::sources::desk_vgen::impls::win32
{
void
CaptureDeskImplWin32::get_buf_int (
  const syn::SourceImplInfo& props_info,
  CaptureDeskInfo&           info)
{
  constexpr std::int32_t dest_bits = 24;

  {
    RECT                                                    window_rect  = { 0, 0, 0, 0 };
    POINT                                                   offset_pos   = { 0, 0 };
    const auto                                              display_name = props_info.props_->ext_vals_.at (consts::param_keys::display_name);
    ::libs::helpers::platforms::win32::HandlerGdiObj< HDC > hdc (CreateDCA ("DISPLAY", display_name.c_str (), nullptr, nullptr));

    window_rect.right  = GetDeviceCaps (*hdc, HORZRES);
    window_rect.bottom = GetDeviceCaps (*hdc, VERTRES);
    // U3_LOG_APPL_MARK (VTOLOG (window_rect.right) + VTOLOG (window_rect.bottom));

#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
    std::uint32_t   dev_index = 0;
    DISPLAY_DEVICEA _DisplayDevice;

    memset (&_DisplayDevice, 0, sizeof (_DisplayDevice));
    _DisplayDevice.cb = sizeof (_DisplayDevice);

    // while (EnumDisplayDevicesA ("DISPLAY", dev_index, &_DisplayDevice, EDD_GET_DEVICE_INTERFACE_NAME))
    while (EnumDisplayDevicesA (nullptr, dev_index, &_DisplayDevice, 0))
    {
      if (_DisplayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
      {
        const std::string display_device = _DisplayDevice.DeviceName;
        const std::string display_string = _DisplayDevice.DeviceString;

        U3_LOG_APPL_MARK (VTOLOG (dev_index) + TOLOG (display_device) + TOLOG (display_string));
      }

      memset (&_DisplayDevice, 0, sizeof (_DisplayDevice));
      _DisplayDevice.cb = sizeof (_DisplayDevice);

      ++dev_index;
    };
#  endif

#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
    const auto window = GetDesktopWindow ();
    U3_CHECK_WIN32_CALL (GetClientRect (window, &window_rect), "GetClientRect");
#  endif

    switch (props_info.capture_props_->capi_.type_capture_)
    {
    case ::libs::ievents::props::videos::generic::driver::CatchRgns::cursor_area: {
      info.width_dest_  = props_info.capture_props_->capi_.width_;
      info.height_dest_ = props_info.capture_props_->capi_.height_;

      U3_CHECK_WIN32_CALL (GetPhysicalCursorPos (&offset_pos), "GetCursorPos");
      // U3_CHECK (PhysicalToLogicalPoint (window, &offset_pos), "PhysicalToLogicalPoint" + VTOLOG (GetLastError ()));
      // U3_CHECK (LogicalToPhysicalPointForPerMonitorDPI (window, &offset_pos), "PhysicalToLogicalPointForPerMonitorDPI" + VTOLOG (GetLastError ()));

      std::int32_t loc_x = offset_pos.x - info.width_dest_ / 2;
      std::int32_t loc_y = offset_pos.y - info.height_dest_ / 2;

      ::libs::helpers::utils::check_bound (loc_x, 0, U3_CAST_INT32 ((window_rect.right - window_rect.left) - info.width_dest_));
      ::libs::helpers::utils::check_bound (loc_y, 0, U3_CAST_INT32 ((window_rect.bottom - window_rect.top) - info.height_dest_));

      offset_pos.x = loc_x;
      offset_pos.y = loc_y;
      break;
    }
    case ::libs::ievents::props::videos::generic::driver::CatchRgns::hwnd:
    case ::libs::ievents::props::videos::generic::driver::CatchRgns::desktop:
    case ::libs::ievents::props::videos::generic::driver::CatchRgns::selection:
    default: {
      info.width_dest_  = props_info.capture_props_->capi_.width_;
      info.height_dest_ = props_info.capture_props_->capi_.height_;
      break;
    }
    }

    ::dlls::sources::desk_vgen::impls::win32::helpers::hdc2rgb (
      *hdc,
      info.rgb_buf_,
      offset_pos.x,
      offset_pos.y,
      info.size_dest_data_,
      info.width_dest_,
      info.height_dest_,
      info.stride_dest_,
      dest_bits);
  }
}
}   // namespace dlls::sources::desk_vgen::impls::win32

#endif
