#pragma once
/**
\file       action-for-list-logs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

std::string to_string (const LogActions& act);
void        tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const LogActions& src);
LogActions  tag_invoke (::boost::json::value_to_tag< LogActions >, const ::boost::json::value& jv);
}   // namespace libs::ilog_events::events
