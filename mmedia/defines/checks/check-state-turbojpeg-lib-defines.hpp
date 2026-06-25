#pragma once
/**
\file       check-state-turbojpeg-lib-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       02.10.2024
\project    u3_defines
*/

#ifndef U3_CHECK_TURBO_JPEG_IMPL
#  define U3_CHECK_TURBO_JPEG_IMPL(u3def_minfo)                                                                                        \
    {                                                                                                                                  \
      const char*       jerr = tjGetErrorStr ();                                                                                       \
      const std::string err  = std::string ("jpeg coder ") + u3def_minfo + std::string (jerr ? jerr : "unknown null turbojpeg error"); \
      U3_LOG_DATA_ERROR (err);                                                                                                         \
      U3_ASSERT_CHECK_CALL (err);                                                                                                      \
    }
#endif

#ifndef U3_CHECK_TURBO_JPEG
#  define U3_CHECK_TURBO_JPEG(u3def_x, u3def_minfo) \
    if (!(u3def_x))                                 \
    {                                               \
      U3_CHECK_TURBO_JPEG_IMPL (u3def_minfo);       \
    }
#endif

#ifndef U3_CHECK_TURBO_JPEG
#  define U3_CHECK_TURBO_JPEG(u3def_x, u3def_minfo) \
    if (!(u3def_x))                                 \
    {                                               \
      U3_CHECK_TURBO_JPEG_IMPL (u3def_minfo);       \
    }
#endif

#ifndef U3_CHECK_TURBO_JPEG_RET
#  define U3_CHECK_TURBO_JPEG_RET(u3def_x, u3def_minfo, u3def_ret) \
    if (!(u3def_x))                                                \
    {                                                              \
      U3_CHECK_TURBO_JPEG_IMPL (u3def_minfo);                      \
      return u3def_ret;                                            \
    }
#endif
