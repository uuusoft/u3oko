//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_compile.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Выводим определение компилятора системы.
*/
#ifndef UUU_COMPILER_MSC
#if defined(_MSC_VER)
#define UUU_COMPILER_MSC
#endif
#endif

#ifndef UUU_COMPILER_GNUC
#if defined(__GNUC__)
#define UUU_COMPILER_GNUC
#endif
#endif

#ifndef UUU_COMPILER_GNUC
#if defined(__clang__)
#define UUU_COMPILER_CLANG
#endif
#endif
