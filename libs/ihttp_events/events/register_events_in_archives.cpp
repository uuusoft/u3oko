//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       register_events_in_archives.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ihttp_events
\brief      Реализация функции для гарантированного присутствия всех событий и их кода архивного сохранения/восстановления в бинарных файлах системы.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "register_events_in_archives.hpp"

namespace libs { namespace ihttp_events { namespace events {

void
register_events_in_archives ()
{
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ihttp_events::events::BaseHttpEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ihttp_events::events::WrapperHttpEvent);
  UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ihttp_events::events::MemResourceHttpEvent);
  return;
}

}}}      // namespace libs::ihttp_events::events
