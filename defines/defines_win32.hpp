//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_win32.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Набор определений, специфичных для WIN32.
*/
#if defined(UUU_COMPILER_MSC)

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#pragma warning(disable : 4752)
#pragma warning(disable : 4190)
#pragma warning(disable : 4316)
#pragma warning(disable : 4459)

//  Очередное дерьмовое удаление всех макросов в нижних регистрах, характерных для включаемых файлов windows.
//  workaround vs2013/2015/2017
#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#endif
