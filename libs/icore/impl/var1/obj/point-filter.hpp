#pragma once
/**
\file       point-filter.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      Объявление типа точки соединения объекта локальной реализации графа обработки данных.
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj {
/**
  \brief  Тип точки соединения объекта.
  */
enum struct PointFilter
{
  input  = 0,      //< Входная точка объекта.
  output = 1       //< Выходная точка объекта.
};

}}}}}      // namespace libs::icore::impl::var1::obj
