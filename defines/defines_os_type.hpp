//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_os_type.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Файл с идентификаторами ОС, под которые компилируется проект.
*/
#if defined(WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#ifndef UUU_OS_WIN32_DESKTOP
#define UUU_OS_WIN32_DESKTOP
#endif
#endif

#if defined(_WIN32_WCE)
#ifndef UUU_OS_WIN32_CE
#define UUU_OS_WIN32_CE
#endif
#endif

#if defined(__ANDROID__)
#ifndef UUU_OS_ANDROID
#define UUU_OS_ANDROID
#endif
#endif

#if defined(__gnu_linux__) && !defined(__ANDROID__) && !defined(UUU_OS_RASPBERRY)
#ifndef UUU_OS_GNU_LINUX
#define UUU_OS_GNU_LINUX
#endif
#endif

#if defined(WTF_TIZE)
#ifndef UUU_OS_TIZEN
#define UUU_OS_TIZEN
#endif
#endif

#if defined(__APPLE__)
#ifndef UUU_OS_MACX_DESKTOP
#define UUU_OS_MACX_DESKTOP
#endif
#endif

#if !(defined(UUU_OS_WIN32_DESKTOP) || defined(UUU_OS_WIN32_CE) || defined(UUU_OS_ANDROID) || defined(UUU_OS_GNU_LINUX) || defined(UUU_OS_TIZEN) || defined(UUU_OS_MACX_DESKTOP))
#ifndef UUU_OS_RASPBERRY
//  Само определение должно выставляться в скрипте cmake при cross-compile. Но возможно есть способ определить явно.
//#   define UUU_OS_RASPBERRY
#endif
#endif
