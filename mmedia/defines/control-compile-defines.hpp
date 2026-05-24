#pragma once
/**
\file       control-compile-defines.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       28.09.2016
\project    u3_defines
*/
#ifndef U3_CNTRL_DEBUG

#  if defined(_DEBUG) || defined(DEBUG) || defined(DBG)
#    define U3_CNTRL_DEBUG
#  endif

#  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
#    if !defined(NDEBUG)
#      define U3_CNTRL_DEBUG
#    endif
#  endif

#endif

//  Определение включает проверки утверждения динамического состояния системы в релизной сборке.
#ifndef U3_CNTRL_RELEASE_ASSERT
#  define U3_CNTRL_RELEASE_ASSERT
#endif

//  Тестовое определение для оценки влияния проверок на скорость и размер кода.
#ifndef U3_CNTRL_FORCE_SKIP_CHECK_CALL
#  if !defined(U3_CNTRL_DEBUG)
// #   define U3_CNTRL_FORCE_SKIP_CHECK_CALL
#  endif
#endif

//  Определение отключает полностью логирование (в том числе и сами вызовы).
//  спользуется, в частности, для проверки влияния логирования на скорость выполнения и размер бинарников.
#if !defined(U3_CNTRL_DEBUG)
#  ifndef U3CNTRL_DISABLED_LOG
// #   define  U3CNTRL_DISABLED_LOG
#  endif
#endif

//  Определение отключает полностью трассировку в консоль.
//  спользуется, в частности, для проверки влияния логирования на скорость выполнения и размер бинарников.
#ifndef U3_CNTRL_DISABLED_CONSOLE_LOG
// #  define U3_CNTRL_DISABLED_CONSOLE_LOG
#endif

//  Определение отключает генерацию событий через макросы модуля собыитй (в том числе и самым вызовы).
//  спользуется, в частности, для проверки влияния их на скорость выполнения и размер бинарников.
#if !defined(U3_CNTRL_DEBUG)
#  ifndef U3CNTRL_DISABLED_EVENTS_MACROS
// #    define U3CNTRL_DISABLED_EVENTS_MACROS
#  endif
#endif

// Для отладки перехода на NASM
#if !defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
// #  define U3_CNTRL_FORCE_USE_X86_X64_ASM
#endif

// Define отключает заморозку dll в памяти, используется для тестирования
#ifndef U3_CNTRL_DEBUG_DISABLE_FROZEN_DLL_IN_MEMORY
// #  define U3_CNTRL_DEBUG_DISABLE_FROZEN_DLL_IN_MEMORY
#endif

// for thread sanitizer force sync fields
#ifndef U3_FORCE_SYNC_FOR_THREAD_SANITIZER
#  define U3_FORCE_SYNC_FOR_THREAD_SANITIZER
#endif
