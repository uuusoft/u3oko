#pragma once
/**
\file       type-convert-accuracy.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       29.07.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      Обявление структуры для группировки сохраняемых свойств фильтра-конвертора форматов цвета.
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace convert {
/**
  \brief  Перечисление различных режимов конвертирования с точки зрения точности.
  */
enum struct TypeConvertAccuracy
{
  usual = 0,      //< По умолчанию.
  fast  = 1,      //< Самый быстрый.
  best  = 2       //< Самая высокая доступная точность.
};

}}}}}}      // namespace libs::ievents::props::videos::generics::convert
