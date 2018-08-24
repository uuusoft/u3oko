//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       make_fake_objs_this_type_defines.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      Макрос для принудительной генерации всех функции данного типа.
            Применяется, чтобы исключить отсутствие регистрации в архивах boost в многомодульной системе.
*/
#ifndef UUU_MAKE_FAKE_OBJ_THIS_TYPE
#define UUU_MAKE_FAKE_OBJ_THIS_TYPE(obj_type)                     \
  {                                                               \
    volatile obj_type::ptr _temp = std::make_shared<obj_type> (); \
  }
#endif

#ifndef UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE
#define UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE(event_type)                 \
  {                                                                   \
    volatile event_type::ptr _temp = event_type::make_shared_this (); \
  }
#endif
