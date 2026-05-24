#pragma once
/**
\file       align-property.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_lib
*/

namespace libs::optim::mcalls
{
struct AlignProperty final {
  AlignProperty () :
    px_x_ (16), px_y_ (1)
  {
  }

  void
  reset ()
  {
    px_x_ = 16;
    px_y_ = 1;
  }

  void
  self_test () const
  {
    U3_CHECK (::libs::optim::mcalls::helpers::check_mcall_data_align (px_x_), "px_x_ unaligned" + VTOLOG (px_x_));
    U3_CHECK (::libs::optim::mcalls::helpers::check_mcall_data_align (px_y_), "px_y_ unaligned" + VTOLOG (px_y_));
  }

  std::uint32_t px_x_;   //< Выравнивание  по горизонтали в пикселях для всех буферов
  std::uint32_t px_y_;   //< Выравнивае по вертикали в пикселях для всех буферов
};
}   // namespace libs::optim::mcalls
