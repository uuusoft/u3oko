#pragma once
/**
\file       enum-log-process-actions.hpp
\author     Erashov Anton erashov2026@proton.me
\date       09.09.2018
\project    u3_ilog_events
*/

namespace libs::ilog_events::events
{
enum class LogProcessActions : std::uint32_t
{
  get_raw_log = 0x00,   //<
  unknown     = 0xFF    //<
  // get_zip_sessions      = 1 //<
};

// EAI-REFACT
auto to_string (const LogProcessActions&) -> std::string;
auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value&, const LogProcessActions&) -> void;
auto tag_invoke (::boost::json::value_to_tag< LogProcessActions >, const ::boost::json::value&) -> LogProcessActions;
}   // namespace libs::ilog_events::events
