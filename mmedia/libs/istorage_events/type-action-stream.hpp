#pragma once
/**
\file       type-action-stream.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       21.08.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events
{
enum class StreamActions : std::uint32_t
{
  read         = 0x00,   //<
  write        = 0x01,   //<
  modification = 0x02,   //<
  unknown      = 0xFF    //<
};

std::string   to_string (const StreamActions& val);
void          tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const StreamActions& src);
StreamActions tag_invoke (::boost::json::value_to_tag< StreamActions >, const ::boost::json::value& jv);
}   // namespace libs::istorage_events
