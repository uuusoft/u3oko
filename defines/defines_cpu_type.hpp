//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_cpu_type.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Определения типа процессора, под который компилируется система.
*/
#if defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(_M_IX86) || defined(_X86_) || defined(__I86__)
#ifndef UUU_CPU_X86_32
#define UUU_CPU_X86_32
#endif
#endif


#if defined(_M_X64) || defined(__x86_64__)
#ifndef UUU_CPU_X86_64
#define UUU_CPU_X86_64
#endif
#endif


#if defined(UUU_CPU_X86_32) || defined(UUU_CPU_X86_64)
#ifndef UUU_CPU_X86
#define UUU_CPU_X86
#endif
#endif


#if !defined(UUU_CPU_X86)

#if defined(__ARM_ARCH_5__) || defined(__ARM_ARCH_5E__) || defined(__ARM_ARCH_5T__) || defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_5TEJ__)
#ifndef UUU_CPU_ARM_5
#define UUU_CPU_ARM_5
#endif
#endif

#if defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6T2__)
#ifndef UUU_CPU_ARM_6
#define UUU_CPU_ARM_6
#endif
#endif

#if defined(__arm__) || defined(__thumb__) || defined(_M_ARM) || defined(M_ARMT) || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__)
#ifndef UUU_CPU_ARM_7
#define UUU_CPU_ARM_7
#endif
#endif

#if !defined(UUU_CPU_ARM_7)
#if defined(__ARM_ARCH_8__) || defined(__ARM_ARCH_8A__) || defined(__ARM_ARCH_8R__) || defined(__ARM_ARCH_8M__) || defined(__aarch64__)
#ifndef UUU_CPU_ARM_8
#define UUU_CPU_ARM_8
#endif
#endif
#endif

#endif


#if defined(UUU_CPU_ARM_5) || defined(UUU_CPU_ARM_6) || defined(UUU_CPU_ARM_7) || defined(UUU_CPU_ARM_8)
#if !defined(UUU_CPU_ARM)
#define UUU_CPU_ARM
#endif
#endif
