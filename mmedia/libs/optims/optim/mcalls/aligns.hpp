#pragma once
/**
\file       aligns.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_optim_lib
*/

namespace libs::optim::mcalls
{
struct Aligns final {
  Aligns ()  = default;
  ~Aligns () = default;

  void
  reset ()
  {
    ax_ = 16;
    ay_ = 1;
  }

  void
  self_test () const
  {
    U3_CHECK (::libs::optim::mcalls::helpers::check_mcall_align (ax_), "x unaligned" + VTOLOG (ax_));
    U3_CHECK (::libs::optim::mcalls::helpers::check_mcall_align (ay_), "y unaligned" + VTOLOG (ay_));
  }

  std::uint32_t ax_ { 16 };   //< Выравнивание  по горизонтали в пикселях для всех буферов
  std::uint32_t ay_ { 1 };    //< Выравнивае по вертикали в пикселях для всех буферов
};
}   // namespace libs::optim::mcalls
