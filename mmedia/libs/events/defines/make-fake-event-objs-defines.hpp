#pragma once
/**
\file       make-fake-event-objs-defines.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_events
\brief      Макрос для принудительной генерации всех функции данного типа
            Применяется, чтобы исключить отсутствие регистрации в архивах boost в многомодульной системе.
*/

#ifndef U3_HELPER_MAKE_FAKE_OBJ_THIS_TYPE
#  define U3_HELPER_MAKE_FAKE_OBJ_THIS_TYPE(U3OBJ_TYPE)                  \
    {                                                                    \
      volatile U3OBJ_TYPE::ptr temp = std::make_shared< U3OBJ_TYPE > (); \
    }
#endif


#ifndef U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE
#  define U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE(U3EVENT_TYPE)                   \
    {                                                                      \
      volatile U3EVENT_TYPE::ptr temp = U3EVENT_TYPE::make_shared_this (); \
    }
#endif
