#pragma once
/**
\file       last-error-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       11.08.2024
*/

namespace libs::utility::platforms::win32
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

inline auto
throw_ifn (const auto& aop, std::source_location location = std::source_location::current ()) -> void
{
  if (!aop)
  {
    ::libs::utility::checks::throw_exception (last_error2string (GetLastError ()), location);
  }
}

inline auto
test (const auto& aop, std::source_location location = std::source_location::current ()) -> void
{
  if (!aop)
  {
    ::libs::utility::checks::test (false, last_error2string (GetLastError ()), location);
  }
}
}   // namespace libs::utility::platforms::win32
