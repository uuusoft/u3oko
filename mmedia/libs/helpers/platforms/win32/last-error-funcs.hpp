#pragma once
/**
\file       last-error-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       11.08.2024
\project    u3_helpers_lib
*/

namespace libs::helpers::platforms::win32
{
inline std::string
last_error2string (unsigned long error)
{
  constexpr std::uint32_t max_size      = 5 * 128;
  char                    buf[max_size] = { '\0' };

  const std::size_t size = FormatMessageA (
    FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    error,
    MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
    buf,
    max_size - 1,
    nullptr);

  if (0 == size)
  {
    return {};
  }

  buf[size] = '\0';
  return std::string (buf, size);
}

#ifndef U3_CHECK_WIN32_CALL
#  define U3_CHECK_WIN32_CALL(x, minfo) U3_CHECK (x, minfo + " error" + ::libs::helpers::platforms::win32::last_error2string (GetLastError ()))
#endif

#ifndef U3_CHECK_WIN32_CALL_NT
#  define U3_CHECK_WIN32_CALL_NT(x, minfo) U3_CHECK_NT (x, minfo + " error=" + ::libs::helpers::platforms::win32::last_error2string (GetLastError ()))
#endif

#ifndef U3_CHECK_WIN32_STATE
#  define U3_CHECK_WIN32_STATE(x, minfo) U3_CHECK (x, minfo + " error=" + ::libs::helpers::platforms::win32::last_error2string (GetLastError ()))
#endif
}   // namespace libs::helpers::platforms::win32
