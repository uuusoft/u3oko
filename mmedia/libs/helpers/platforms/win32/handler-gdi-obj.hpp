#pragma once
/**
\file       handler-gdi-obj.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       12.05.2022
\project    u3_helpers_lib
*/

namespace libs::helpers::platforms::win32
{
template< typename TTGDIObj >
class HandlerGdiObj final
{
  public:
  U3_HELPER_DISABLE_ACOPY_TYPE (HandlerGdiObj)

  explicit HandlerGdiObj (const TTGDIObj& obj = 0) :
    obj_ (obj)
  {
  }

  ~HandlerGdiObj ()
  {
    libs::helpers::platforms::win32::safe_delete_gdi_object< TTGDIObj > (obj_);
  }

  operator bool () const
  {
    return obj_ ? true : false;
  }

  TTGDIObj
  operator* ()
  {
    return obj_;
  }

  void
  change_gdi_object (const TTGDIObj& obj)
  {
    libs::helpers::platforms::win32::safe_delete_gdi_object< TTGDIObj > (obj_);
    obj_ = obj;
  }

  private:
  TTGDIObj obj_;   //<
};


class HandlerWindowDC
{
  public:
  U3_HELPER_DISABLE_ACOPY_TYPE (HandlerWindowDC)

  explicit HandlerWindowDC (const HWND& hwnd) :
    hwnd_ (hwnd)
  {
    hdc_ = GetDC (hwnd_);
    if (nullptr == hdc_)
    {
      U3_XLOG_ERROR ("GetDC for window" + PTR_TOLOG (hwnd_) + VTOLOG (GetLastError ()));
    }
  }

  ~HandlerWindowDC ()
  {
    if (nullptr == hdc_)
    {
      return;
    }
    if (1 != ReleaseDC (hwnd_, hdc_))
    {
      U3_XLOG_ERROR ("ReleaseDC for window" + PTR_TOLOG (hwnd_) + VTOLOG (GetLastError ()));
    }
  }

  operator bool () const
  {
    return hdc_ ? true : false;
  }

  HDC
  operator* ()
  {
    return hdc_;
  }

  private:
  HWND hwnd_;   //<
  HDC  hdc_;    //<
};


class HandlerCompatibleDC
{
  public:
  U3_HELPER_DISABLE_ACOPY_TYPE (HandlerCompatibleDC)

  explicit HandlerCompatibleDC (HDC hdc) :
    hdc_ (nullptr),
    original_bitmap_ (nullptr)
  {
    U3_CHECK_WIN32_STATE (hdc_ = CreateCompatibleDC (hdc), "CreateCompatibleDC");
  }

  ~HandlerCompatibleDC ()
  {
    if (hdc_ && original_bitmap_)
    {
      U3_CHECK_WIN32_CALL_NT (SelectObject (hdc_, original_bitmap_), "SelectObject for original bitmap");
    }

    safe_delete_gdi_object (hdc_);
  }

  HBITMAP
  select_object (HBITMAP obj)
  {
    if (nullptr == original_bitmap_)
    {
      U3_CHECK_WIN32_STATE (original_bitmap_ = U3_CAST_STATIC< HBITMAP > (SelectObject (hdc_, obj)), "SelectObject");
    }
    return original_bitmap_;
  }

  operator bool () const
  {
    return hdc_ ? true : false;
  }

  HDC
  operator* ()
  {
    return hdc_;
  }

  private:
  HDC     hdc_;               //<
  HBITMAP original_bitmap_;   //<
};
}   // namespace libs::helpers::platforms::win32
