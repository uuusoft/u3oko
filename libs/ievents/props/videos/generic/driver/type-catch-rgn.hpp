//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       type-catch-rgn.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace driver {
/**
  \brief  Перечисление различных регионов при захвате изображения с экрана.
  */
enum struct TypeCatchRgn : unsigned int
{
  usual       = 0,      //< Значение по умолчанию для общности.
  desktop     = 1,      //< Десктоп.
  hwnd        = 2,      //< Указанное окно.
  selection   = 3,      //< Выделение из дескотопа.
  cursor_area = 4       //< Область связанная с курсором.
};

}}}}}}      // namespace libs::ievents::props::videos::generics::driver
