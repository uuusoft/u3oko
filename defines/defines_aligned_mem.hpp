#pragma once
/**
\file       defines_aligned_mem.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Обявление спецификаторов памяти, общих для всей системы.
*/
#ifndef UUU_ALIGNED_MEM_CAST
#define UUU_ALIGNED_MEM_CAST reinterpret_cast
#endif


#if defined(UUU_OS_WIN32_DESKTOP)
#define ALIGNED32 __declspec(align (32))
#define ALIGNED64 __declspec(align (64))
#else
#define ALIGNED32 alignas (32)
#define ALIGNED64 alignas (64)
#endif


#if defined(UUU_CPU_X86)

#if defined(UUU_CPU_X86_32)
#define UUU_DEFAULT_ALIGNED ALIGNED32
#else
#define UUU_DEFAULT_ALIGNED ALIGNED32
#endif

#elif defined(UUU_CPU_ARM)
#define UUU_DEFAULT_ALIGNED ALIGNED32
#else
#error select OS
#endif
