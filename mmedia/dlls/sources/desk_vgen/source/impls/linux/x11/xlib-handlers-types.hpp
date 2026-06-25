#pragma once
/**
\file       xlib-handlers-types.hpp
\author     Erashov Anton erashov2026@proton.me
\date       17.05.2022
\project    u3_desk_vgen
*/
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
// #if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
#  include <X11/Xlib.h>
#  include <X11/Xutil.h>

namespace dlls::sources::desk_vgen::impls::linux::x11
{
template< typename TTObj, std::int32_t (*free_funct) (TTObj*) >
class HandlerXLibObj final
{
  public:
  U3_HELPER_DISABLE_ACOPY_TYPE (HandlerXLibObj)

  explicit HandlerXLibObj (TTObj* obj = nullptr) :
    obj_ (obj)
  {
  }

  ~HandlerXLibObj ()
  {
    if (obj_)
    {
      free_funct (obj_);
    }
  }

  operator bool () const
  {
    return obj_ ? true : false;
  }

  TTObj*
  operator* ()
  {
    return obj_;
  }

  void
  change_xlib_object (TTObj* obj)
  {
    if (obj_)
    {
      free_funct (obj_);
    }
    obj_ = obj;
  }

  private:
  TTObj* obj_;   //<
};


inline std::int32_t
helper_XDestroyImage (XImage* obj)
{
  XDestroyImage (obj);
  return 0;
}

using xlib_display_type = HandlerXLibObj< Display, XCloseDisplay >;
using xlib_image_type   = HandlerXLibObj< XImage, helper_XDestroyImage >;
}   // namespace dlls::sources::desk_vgen::impls::linux::x11

#endif
