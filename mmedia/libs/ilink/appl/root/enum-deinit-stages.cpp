#pragma once
/**
\file       enum-deinit-stages.cpp
\author     Erashov Anton erashov2026@proton.me
\date       10.11.2026
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "enum-deinit-stages.hpp"

namespace libs::ilink::appl::root
{
auto
to_string (const DeInitStages& val) noexcept -> const std::string&
{
  static const boost::unordered_flat_map< DeInitStages, const std::string > vals = {
    { DeInitStages::start_send_stop_msgs, "start_send_stop_msgs" },
    { DeInitStages::wait_stop_test_module, "wait_stop_test_module" },
    { DeInitStages::wait_stop_http_module, "wait_stop_http_module" },
    { DeInitStages::wait_stop_net_module, "wait_stop_net_module" },
    { DeInitStages::wait_stop_ai_module, "wait_stop_ai_module" },
    { DeInitStages::wait_stop_gui_module, "wait_stop_gui_module" },
    { DeInitStages::wait_stop_rtp_module, "wait_stop_rtp_module" },
    { DeInitStages::wait_stop_data_module, "wait_stop_data_module" },
    { DeInitStages::wait_stop_storage_module, "wait_stop_storage_module" },
    { DeInitStages::wait_stop_events_module, "wait_stop_events_module" },
    { DeInitStages::wait_stop_users_module, "wait_stop_users_module" },
    { DeInitStages::send_stop_msg2log_module, "send_stop_msg2log_module" },
    { DeInitStages::wait_stop_log_module, "wait_stop_log_module" },
    { DeInitStages::done, "done" },
    { DeInitStages::unknown, "unknown" }
  };

  auto finger = vals.find (val);
  if (vals.end () == finger)
  {
    U3_XLOG_ERROR ("Unknown value DeInitStages");
    finger = vals.find (DeInitStages::unknown);
  }
  return finger->second;
}
}   // namespace libs::ilink::appl::root
