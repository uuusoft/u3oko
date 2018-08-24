//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       type-dim-var.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Типы переменных, контролирущих геометрию буфера.
*/

namespace utils { namespace dbuffs { namespace video {
/**
  \brief  Перечисление типов переменных, описывающих геометрию буфера с данными.
  */
enum struct TypeDimVar
{
  stride    = 0,      //< Шаг строки буфера в байтах
  width     = 1,      //< Размер ширины буфера в пикселях.
  height    = 2,      //< Размер высоты буфера в пикселях.
  max_bound = 4       //< Максимальное значение данного типа для определения массивов.
};

}}}      // namespace utils::dbuffs::video
