/**
\file       process-helper-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_helpers_lib
*/
#include "../utility-lib-includes_int.hpp"
#include "process-helper-funcs.hpp"

namespace libs::utility::process
{
auto
get_id () -> std::int32_t
{
  return getpid ();
}


auto
get_start_time () -> std::int64_t
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
  std::ifstream infile ("/proc/stat");
  std::string   line;
  while (std::getline (infile, line))
  {
    if (line.starts_with ("btime"))
    {
      std::istringstream iss (line);
      std::string        label;
      if (iss >> label >> ret)
      {
        break;
      }
    }
  }
#endif
  return ret;
}
}   // namespace libs::utility::process
