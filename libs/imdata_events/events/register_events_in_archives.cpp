//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       events2archives.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      ќбъ€вление функции дл€ гарантированного присутстви€ всех событий и их кода архивного сохранени€/восстановлени€ в бинарных файлах системы.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "register_events_in_archives.hpp"

namespace libs { namespace imdata_events { namespace events {

void
register_events_in_archives ()
{
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::BaseDataEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::GetNodesDataEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::ChangePathsDataEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::ListDevicesDataEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::ListXmlFilesDataEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::BaseNodesDataEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::ChangeNodeDataEvent);
  return;
}

}}}      // namespace libs::imdata_events::events
