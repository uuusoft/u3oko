#pragma once
/**
\file       enum-deinit-stages.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.07.2018
\project    u3_ilink
*/

namespace libs::ilink::appl::root
{
enum class DeInitStages : std::uint32_t
{
  send_stop_msg2allmost_all = 0x00,   //<
  wait_stop_data_module     = 0x01,   //<
  wait_stop_gui_module      = 0x02,   //<
  wait_stop_rtp_module      = 0x03,   //<
  wait_stop_storage_module  = 0x04,   //<
  wait_stop_events_module   = 0x05,   //<
  send_stop_msg2log_module  = 0x06,   //<
  wait_stop_log_module      = 0x07,   //<
  wait_stop_http_module     = 0x08,   //<
  done                      = 0x09,   //<
  unknown                   = 0xFF    //<
};
}   // namespace libs::ilink::appl::root
