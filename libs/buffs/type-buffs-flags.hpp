//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       type-buffs-flags.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_buffs
\brief      empty brief
*/

namespace libs { namespace buffs {
/**
\brief  Перечисление различных флагов, общих для всего Buffs.
*/
enum struct TypeBuffsFlags
{
  empty               = 0,      //< Флаг отсутствия данных.
  request_convert2hsl = 1,      //< Флаг требования произвести конвертацию в HSL (или обновить HSL) из буфера с оригинальными данными (RGB24/YUY2/I420/etc).
  max_bound           = 16      //< Максимальное значение типа для границы.
};

}}      // namespace libs::buffs
