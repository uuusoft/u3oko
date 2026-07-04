/**
\file       enum-stream-actions.cpp
\author     Erashov Anton erashov2026@proton.me
\date       24.06.2022
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "events-user-includes_int.hpp"
#include "enum-user-actions.hpp"

namespace libs::events_user
{
#if 0  
// EAI-REFACT
std::string
to_string (const UserActions& val)
{
  switch (val)
  {
  case UserActions::read:
    return "read";
  case UserActions::write:
    return "write";
  case UserActions::modification:
    return "modification";
  case UserActions::unknown:
    return "unknown";
  }
  U3_XLOG_WARN ("unknown UserActions" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
  return "xxx";
}
#endif
}   // namespace libs::events_user
