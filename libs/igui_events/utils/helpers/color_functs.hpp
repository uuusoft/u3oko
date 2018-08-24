#pragma once
/**
\file       color_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace utils { namespace helpers {

inline Color
make_rand ()
{
  return Color (rand () % 255, rand () % 255, rand () % 255);
}

}}}}      // namespace libs::igui_events::utils::helpers
