//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       type-check-dim.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Режимы проверки границ буфера.
*/

namespace utils { namespace dbuffs { namespace video {
/**
\brief  Перечисление различных режимов проверок при использовании буфера с данными.
*/
enum struct TypeCheckDim
{
  disabled_check = 0,      //< Отключить автоматическую проверку границ.
  enable_check   = 1       //< Включить автоматическую проверку границ буфера.
};

}}}      // namespace utils::dbuffs::video
