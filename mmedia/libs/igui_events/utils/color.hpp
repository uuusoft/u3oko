#pragma once
/**
\file       color.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_igui_events
*/

namespace libs::igui_events::utils
{
class Color
{
  public:
  explicit Color (std::uint16_t r = 0, std::uint16_t g = 0, std::uint16_t b = 0) :
    r_ (r),
    g_ (g),
    b_ (b)
  {
  }

  std::uint16_t
  get_r () const
  {
    return r_;
  }

  std::uint16_t
  get_g () const
  {
    return g_;
  }

  std::uint16_t
  get_b () const
  {
    return b_;
  }

  private:
  std::uint16_t r_;   //<
  std::uint16_t g_;   //<
  std::uint16_t b_;   //<
};
}   // namespace libs::igui_events::utils
