/**
\file       sync-objs-action.cpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "sync-objs-action.hpp"

namespace libs::ievents::runtime::control
{
std::string
to_string (const SyncActions& val)
{
  switch (val)
  {
  case SyncActions::info:
    return "info";
  case SyncActions::sync:
    return "sync";
  case SyncActions::uplink:
    return "uplink";
  case SyncActions::downlink:
    return "downlink";
  case SyncActions::start:
    return "start";
  case SyncActions::stop:
    return "stop";
  case SyncActions::empty:
    return "empty";
  case SyncActions::unknown:
    return "unknown";
  default:
    U3_XLOG_ERROR ("unknown SyncActions" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    return "unknown SyncActions";
  }
}
}   // namespace libs::ievents::runtime::control
