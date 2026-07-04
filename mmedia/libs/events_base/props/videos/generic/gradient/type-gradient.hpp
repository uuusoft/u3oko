#pragma once
/**
\file       type-gradient.hpp
\author     Erashov Anton erashov2026@proton.me
\date       28.05.2022
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::gradient
{
enum class Gradients : std::uint32_t
{
  skip             = 0x00,   //<
  usual            = 0x01,   //<
  set2min          = 0x02,   //<
  set2max          = 0x03,   //<
  load_from_file   = 0x04,   //<
  load_from_string = 0x05,   //<
  rnd              = 0x06,   //<
  increment        = 0x07,   //<
  direct           = 0x08,   //<
  unknown          = 0xFF    //<
};

void      tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Gradients& src);
Gradients tag_invoke (::boost::json::value_to_tag< Gradients >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::videos::generic::gradient
