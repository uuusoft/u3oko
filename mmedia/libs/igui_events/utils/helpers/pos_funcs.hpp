#pragma once
/**
\file       pos_funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_igui_events
*/

namespace libs::igui_events::utils::helpers
{
inline bool
is_equal (IPos::craw_ptr left, IPos::craw_ptr right)
{
  U3_ASSERT (left);
  U3_ASSERT (right);

  if (left == right)
  {
    return true;
  }

  if (left->get_x () != right->get_x ())
  {
    return false;
  }

  if (left->get_y () != right->get_y ())
  {
    return false;
  }

  return true;
}
}   // namespace libs::igui_events::utils::helpers
