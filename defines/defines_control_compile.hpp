#pragma once
/**
\file       defines_control_compile.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       28.09.2016.
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      empty brief
*/
#ifndef UUU_DEBUG

#if defined(_DEBUG) || defined(DEBUG) || defined(DBG)
#define UUU_DEBUG
#endif

#if defined(UUU_COMPILER_GNUC) || defined(UUU_COMPILER_CLANG)
#if !defined(NDEBUG)
#define UUU_DEBUG
#endif
#endif

#endif

//  Определение включает проверки утверждения динамического состояния системы в релизной сборке.
#ifndef UUU_ENABLE_ASSERT_IN_RELEASE
#define UUU_ENABLE_ASSERT_IN_RELEASE
#endif

//  Тестовое определение для оценки влияния проверок на скорость и размер кода.
#ifndef UUU_FORCE_SKIP_CHECK_CALL
#if !defined(UUU_DEBUG)
//#   define UUU_FORCE_SKIP_CHECK_CALL
#endif
#endif

//  Определение отключает полностью логиирование (в том числе и самым вызовы).
//  Используется, в частности, для проверки влияния их на скорость выполнения и размер бинарников.
#if !defined(UUU_DEBUG)
#ifndef UUU_DISABLED_LOG
//#   define  UUU_DISABLED_LOG
#endif
#endif

//  Определение отключает генерацию событий через макросы модуля собыитй (в том числе и самым вызовы).
//  Используется, в частности, для проверки влияния их на скорость выполнения и размер бинарников.
#if !defined(UUU_DEBUG)
#ifndef UUU_DISABLED_EVENTS_MACROS
//#   define  UUU_DISABLED_EVENTS_MACROS
#endif
#endif
