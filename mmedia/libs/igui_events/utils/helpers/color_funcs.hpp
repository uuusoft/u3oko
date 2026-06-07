#pragma once
/**
\file       color_funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017

\project    u3_igui_events
*/

namespace libs::igui_events::utils::helpers
{
inline Color
make_rand ()
{
  return Color (rand () % 255, rand () % 255, rand () % 255);
}
}   // namespace libs::igui_events::utils::helpers
