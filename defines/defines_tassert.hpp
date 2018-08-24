//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_tassert.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
*/
namespace base_functs { namespace consts { namespace strings {

const std::string str_assert = std::string ("uuu_assert: ");      //< Строка по умолчанию, идентифицирующая событие "assert".

}}}      // namespace base_functs::consts::strings
/**
\brief  Обычная отладочная проверка динамического утверждение.
*/
#ifndef ASSERT
#define ASSERT(_x_) assert (_x_)
#endif
/**
\brief  Определение для возможности отключения генерации исключений при включенном логировании.
\brief  Иногда полезно просто фиксировать наличии состояний, без генерации исключений, в частности для проверки системы в динамическом режиме
*/
#ifndef TASSERT
//#define TASSERT(_x_) ASSERT (_x_)
#define TASSERT(_x_)
#endif
