#pragma once
/**
\file       size_funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017

*/

namespace libs::events_gui::utils::helpers
{
inline bool
is_equal (ISize::craw_ptr left, ISize::craw_ptr right)
{
  ::libs::utility::checks::throw_ifn (left);
  ::libs::utility::checks::throw_ifn (right);

  if (left == right)
  {
    return true;
  }

  if (left->get_width () != right->get_width ())
  {
    return false;
  }

  if (left->get_height () != right->get_height ())
  {
    return false;
  }

  return true;
}
}   // namespace libs::events_gui::utils::helpers
