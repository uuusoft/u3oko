#pragma once
/**
\file       type-src2dst.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       29.07.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      Обявление структуры для группировки сохраняемых свойств фильтра-конвертора форматов цвета.
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace convert {
/**
  \brief Перечисление для режимов соответствия размеров назначания и источника.
  */
enum struct TypeSrc2Dst
{
  src_int_dst  = 0,      //< ???
  src_int_dst2 = 1,      //< ???
  equal_dst    = 2,      //< ???
  additive     = 3       //< ???
};

}}}}}}      // namespace libs::ievents::props::videos::generics::convert
