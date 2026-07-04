#pragma once
/**
\file       enum-stream-actions.hpp
\author     Erashov Anton erashov2026@proton.me
\date       21.08.2018
\project    u3_events_storage
*/

namespace libs::events_storage
{
enum class StreamActions : std::uint32_t
{
  read         = 0x00,   //<
  write        = 0x01,   //<
  modification = 0x02,   //<
  unknown      = 0xFF    //<
};

std::string   to_string (const StreamActions& val);
void          tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const StreamActions& src);
StreamActions tag_invoke (::boost::json::value_to_tag< StreamActions >, const ::boost::json::value& jvs);
}   // namespace libs::events_storage
