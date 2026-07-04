#if 0
#  pragma once
/**
\file       enum-stream-times.hpp
\author     Erashov Anton erashov2026@proton.me
\date       12.08.2018
\project    u3_events_storage
*/

namespace libs::events_storage
{
enum class StreamTimes : std::uint32_t
{
  exactly  = 0x00,   //<
  oldest   = 0x01,   //<
  youngest = 0x02,   //<
  unknown  = 0xFF    //<
};

std::string to_string (const StreamTimes& val);
void        tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const StreamTimes& src);
StreamTimes tag_invoke (::boost::json::value_to_tag< StreamTimes >, const ::boost::json::value& jvs);
}   // namespace libs::events_storage
#endif
