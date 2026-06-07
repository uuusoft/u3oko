#pragma once
/**
\file       enum-convs.hpp
\date       14.06.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::convolution
{
enum class Convs : std::uint32_t
{
  skip      = 0x00,   //<
  use_exist = 0x01,   //<
  all_to_1  = 0x02,   //<
  all_to_m1 = 0x03,   //<
  average   = 0x04,   //<
  spot      = 0x05,   //<
  gaus1     = 0x06,   //<
  gaus2     = 0x07,   //<
  gaus3     = 0x08,   //<
  laplas1   = 0x09,   //<
  laplas2   = 0x0A,   //<
  laplas3   = 0x0B,   //<
  unknown   = 0xFF    //< unknown
};

void  tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Convs& src);
Convs tag_invoke (::boost::json::value_to_tag< Convs >, const ::boost::json::value& jvs);
}   // namespace libs::ievents::props::videos::generic::convolution
