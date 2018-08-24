//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_set_target_cpu.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Определение для уточнения типа процессора, под который собирается конкретная функция.
*/
#ifndef UUU_SET_TARGET_CPU

#if defined(UUU_COMPILER_MSC)
#define UUU_SET_TARGET_CPU(xcpu)
#elif defined(UUU_COMPILER_GNUC)
#define UUU_SET_TARGET_CPU(xcpu) [[gnu::target (#xcpu)]]
#elif defined(UUU_COMPILER_CLANG)
#define UUU_SET_TARGET_CPU(xcpu) [[gnu::target (#xcpu)]]
#else
#error "requared define compile"
#endif

#endif
