#pragma once
/**
\file       enum-stream-updates.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.07.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events
{
enum class StreamUpdates : std::uint32_t
{
  open               = 0x00,   //<
  close              = 0x01,   //<
  check_and_get_info = 0x02,   //<
  change             = 0x03,   //<
  unknown            = 0xFF    //<
};

const std::string& to_string (const StreamUpdates& val);
void               tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const StreamUpdates& src);
StreamUpdates      tag_invoke (::boost::json::value_to_tag< StreamUpdates >, const ::boost::json::value& jvs);
}   // namespace libs::istorage_events
