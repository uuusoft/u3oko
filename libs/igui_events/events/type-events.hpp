#pragma once
/**
\file       type-events.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace events {
/**
  \brief  empty brief
  */
enum struct TypeEvents
{
  unknow         = 0,      //< ???
  base           = 1,      //< ???
  exit_appl      = 2,      //< ???
  load_xml2frame = 3,      //< ???
  mem_block      = 4,      //< ???
  video_buff     = 5,      //< ???
  update_draw    = 6,      //< ???
  size_changed   = 7,      //< ???
  command_code   = 8,      //< ???
  mbutton_down   = 9,      //< ???
  mbutton_up     = 10      //< ???
};

}}}      // namespace libs::igui_events::events
