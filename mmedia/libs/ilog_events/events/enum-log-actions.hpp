#pragma once
/**
\file       enum-log-actions.hpp
\author     Erashov Anton erashov2026@proton.me
\date       09.09.2018
\project    u3_ilog_events
*/

namespace libs::ilog_events::events
{
enum class LogActions : std::uint32_t
{
  get_sessions    = 0x00,   //<
  delete_sessions = 0x01,   //<
  unknown         = 0xFF    //<
};

// EAI-REFACT
auto to_string (const LogActions&) -> std::string;
auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value&, const LogActions&) -> void;
auto tag_invoke (::boost::json::value_to_tag< LogActions >, const ::boost::json::value&) -> LogActions;
}   // namespace libs::ilog_events::events
