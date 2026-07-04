#pragma once
/**
\file       color_funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017

\project    u3_events_gui
*/

namespace libs::events_gui::utils::helpers
{
inline Color
make_rand ()
{
  return Color (rand () % 255, rand () % 255, rand () % 255);
}
}   // namespace libs::events_gui::utils::helpers
