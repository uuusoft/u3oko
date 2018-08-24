#pragma once
/**
\file       run-state-filter.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      Объявление типа состояния в котором может находится объект графа обработки данных. 
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj {
/**
  \brief  Тип-состояния объекта графа.
  */
enum struct RunStateFilter
{
  stop = 0,      //< Объект остановлен.
  run  = 1       //< Объект запущен.
};

}}}}}      // namespace libs::icore::impl::var1::obj
