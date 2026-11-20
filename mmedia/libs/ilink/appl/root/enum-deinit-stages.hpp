#pragma once
/**
\file       enum-deinit-stages.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.07.2018
*/

namespace libs::ilink::appl::root
{
/// Стадии завершения приложения
enum class DeInitStages : std::uint32_t
{
  start_send_stop_msgs = 0,   //<
  wait_stop_test_module,      //<
  wait_stop_http_module,      //<
  wait_stop_net_module,       //<
  wait_stop_ai_module,        //<
  wait_stop_gui_module,       //<
  wait_stop_rtp_module,       //<
  wait_stop_data_module,      //<
  wait_stop_storage_module,   //<
  wait_stop_events_module,    //<
  wait_stop_users_module,     //<
  send_stop_msg2log_module,   //<
  wait_stop_log_module,       //<
  done    = 0xFFFE,           //<
  unknown = 0xFFFF            //<
};

auto to_string (const DeInitStages& val) noexcept -> const std::string&;
}   // namespace libs::ilink::appl::root
