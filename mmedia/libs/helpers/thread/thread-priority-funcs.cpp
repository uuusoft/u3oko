/**
\file       thread-priority-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       11.05.2022
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "priorities-enum.hpp"

namespace libs::helpers::thread
{
// EAI-REFACT
std::string
to_string (const Priorities& val)
{
  switch (val)
  {
  case Priorities::freeze:
    return "freeze";
  case Priorities::idle:
    return "idle";
  case Priorities::low:
    return "low";
  case Priorities::below_normal:
    return "below_normal";
  case Priorities::normal:
    return "normal";
  case Priorities::above_normal:
    return "above_normal";
  case Priorities::high:
    return "high";
  case Priorities::time_critical:
    return "time_critical";
  case Priorities::unknown:
    return "unknown";
  default:
    U3_XLOG_ERROR ("unknown Priorities" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    return "unknown Priorities";
  }
}


void
set_thread_priority (const std::thread::id& thread, const Priorities& val)
{
  U3_XLOG_DBG ("change priority thread " << thread << " to " + to_string (val));
#ifdef U3_OS_WIN32_DESKTOP
#elif defined(U3_OS_ANDROID)
#elif defined(U3_OS_MACX_DESKTOP)
#elif defined(U3_OS_GNU_LINUX)
#elif defined(U3_OS_RASPBERRY)
#elif defined(U3_OS_ORANGE_PI)
#else
#  pragma error "unknown os type for set_thread_priority";
#endif
}
}   // namespace libs::helpers::thread
