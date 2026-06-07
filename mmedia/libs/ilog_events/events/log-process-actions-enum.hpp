#pragma once
/**
\file       log-process-actions-enum.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

std::string       to_string (const LogProcessActions& val);
void              tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const LogProcessActions& src);
LogProcessActions tag_invoke (::boost::json::value_to_tag< LogProcessActions >, const ::boost::json::value& jvs);
}   // namespace libs::ilog_events::events
