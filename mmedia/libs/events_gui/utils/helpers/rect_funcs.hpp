#pragma once
/**
\file       rect_funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/

namespace libs::events_gui::utils::helpers
{
inline bool
is_equal (IRect::raw_ptr left, IRect::raw_ptr right)
{
  U3_ASSERT (left);
  U3_ASSERT (right);

  if (left == right)
  {
    return true;
  }

  if (!is_equal (left->get_pos (), right->get_pos ()))
  {
    return false;
  }

  if (!is_equal (left->get_size (), right->get_size ()))
  {
    return false;
  }

  return true;
}


inline bool
include (const IRect::raw_ptr rect, const IPos::raw_ptr pos)
{
  U3_ASSERT (rect);
  U3_ASSERT (pos);

  auto gpos  = rect->get_pos ();
  auto gsize = rect->get_size ();

  return gpos->get_x () <= pos->get_x () &&
         gpos->get_y () >= pos->get_y () &&
         gpos->get_x () + gsize->get_width () >= pos->get_x () &&
         gpos->get_y () - gsize->get_height () <= pos->get_y ();
}
}   // namespace libs::events_gui::utils::helpers
