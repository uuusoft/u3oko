/**
\file       process-helper-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
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
  std::ifstream infile ("/proc/stat");
  std::string   line;
  while (std::getline (infile, line))
  {
    if (line.rfind ("btime", 0) == 0)
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
}   // namespace libs::helpers::process
