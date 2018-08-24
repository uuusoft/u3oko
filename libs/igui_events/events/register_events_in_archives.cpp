//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       register_events_in_archives.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      Реализация функции для гарантированного присутствия всех событий и их кода архивного сохранения/восстановления в бинарных файлах системы.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "register_events_in_archives.hpp"

namespace libs { namespace igui_events { namespace events {

void
register_events_in_archives ()
{
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::BaseGUIEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::CommandCodeEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::ExitApplEvent);
  //UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE( ::libs::igui_events::events::MemBlockEvent );
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::MouseButtonDownEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::MouseButtonUpEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::SizeChangedEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::UpdateDrawEvent);
  //UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE( ::libs::igui_events::events::VideoBuffEvent );
  return;
}

}}}      // namespace libs::igui_events::events
