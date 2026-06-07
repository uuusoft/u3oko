/**
\file       process-helper-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "process-helper-funcs.hpp"

namespace libs::helpers::process
{
std::int32_t
get_id ()
{
  return getpid ();
}


std::int64_t
get_start_time ()
{
  std::int64_t ret = 0;
#ifdef U3_OS_WIN32_DESKTOP
  {
    FILETIME tcreate;
    FILETIME texit;
    FILETIME tkernel;
    FILETIME tuser;

    U3_CHECK (GetProcessTimes (GetCurrentProcess (), &tcreate, &texit, &tkernel, &tuser), "call GetProcessTimes");
    ret = (U3_CAST_INT64 (tcreate.dwHighDateTime) << 32) | tcreate.dwLowDateTime;
  }
#else
  U3_XLOG_UNIMPL ("libs::helpers::process::get_start_time");
#endif
  return ret;
}
}   // namespace libs::helpers::process
