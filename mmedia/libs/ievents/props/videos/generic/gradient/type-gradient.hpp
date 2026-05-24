#pragma once
/**
\file       type-gradient.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       28.05.2022
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::gradient
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

void      tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const Gradients& src);
Gradients tag_invoke (::boost::json::value_to_tag< Gradients >, const ::boost::json::value& jv);
}   // namespace libs::ievents::props::videos::generic::gradient
