#pragma once
/**
\file       enum-stream-directions.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.07.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events
{
enum class StreamDirections : std::uint32_t
{
  forward  = 0x00,   //<
  backward = 0x01,   //<
  unknown  = 0xFF    //<
};

std::string      to_string (const StreamDirections& val);
void             tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const StreamDirections& src);
StreamDirections tag_invoke (::boost::json::value_to_tag< StreamDirections >, const ::boost::json::value& jvs);
}   // namespace libs::istorage_events
