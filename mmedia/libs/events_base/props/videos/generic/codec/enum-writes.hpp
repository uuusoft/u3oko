#pragma once
/**
\file       enum-writes.hpp
\author     Erashov Anton erashov2026@proton.me
\date       29.07.2018
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::codec
{
enum class Writes : std::uint32_t
{
  allways_write      = 0x00,   //<
  write_if_not_empty = 0x01,   //<
  write_if_empty     = 0x02,   //<
  unknown            = 0xFF    //<
};

void   tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Writes& src);
Writes tag_invoke (::boost::json::value_to_tag< Writes >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::videos::generic::codec
