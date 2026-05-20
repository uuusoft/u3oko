#pragma once
/**
\file       os-type-detect-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
\brief      Файл с идентификаторами ОС, под которые компилируется проект.
*/
#if defined(WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#  ifndef U3_OS_WIN32_DESKTOP
#    define U3_OS_WIN32_DESKTOP
#  endif
#endif

#if defined(_WIN32_WCE)
#  ifndef U3_OS_WIN32_CE
#    define U3_OS_WIN32_CE
#  endif
#endif

#if defined(__ANDROID__)
#  ifndef U3_OS_ANDROID
#    define U3_OS_ANDROID
#  endif
#endif

#if defined(__APPLE__) && !defined(__ANDROID__) && !defined(U3_OS_RASPBERRY) && !defined(U3_OS_GNU_LINUX) && !defined(U3_OS_ORANGE_PI)
#  ifndef U3_OS_MACX_DESKTOP
#    define U3_OS_MACX_DESKTOP
#  endif
#endif

#if defined(__gnu_linux__) && !defined(__ANDROID__) && !defined(U3_OS_RASPBERRY) && !defined(U3_OS_MACX_DESKTOP) && !defined(U3_OS_ORANGE_PI)
#  ifndef U3_OS_GNU_LINUX
#    define U3_OS_GNU_LINUX
#  endif
#endif

#if defined(WTF_TIZE) && !defined(__ANDROID__) && !defined(U3_OS_RASPBERRY) && !defined(U3_OS_GNU_LINUX) && !defined(U3_OS_MACX_DESKTOP) && !defined(U3_OS_ORANGE_PI)
#  ifndef U3_OS_TIZEN
#    define U3_OS_TIZEN
#  endif
#endif

#if !(defined(U3_OS_WIN32_DESKTOP) || defined(U3_OS_WIN32_CE) || defined(U3_OS_ANDROID) || defined(U3_OS_GNU_LINUX) || defined(U3_OS_TIZEN) || defined(U3_OS_MACX_DESKTOP) || defined(U3_OS_RASPBERRY))
#  ifndef U3_OS_ORANGE_PI
// #   define U3_OS_ORANGE_PI
#  endif
#endif

#if !(defined(U3_OS_WIN32_DESKTOP) || defined(U3_OS_WIN32_CE) || defined(U3_OS_ANDROID) || defined(U3_OS_GNU_LINUX) || defined(U3_OS_TIZEN) || defined(U3_OS_MACX_DESKTOP) || defined(U3_OS_ORANGE_PI))
#  ifndef U3_OS_RASPBERRY
//  Само определение должно выставляться в скрипте cmake при cross-compile. Но возможно есть способ определить явно.
// #   define U3_OS_RASPBERRY
#  endif
#endif
