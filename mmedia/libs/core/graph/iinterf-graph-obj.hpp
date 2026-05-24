#pragma once
/**
\file       iinterf-graph-obj.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_core_lib
*/

namespace libs::core::graph
{
/// Базовый интерфейс для расширения свойств объекта в графе по обработке данных
/// Запрашивается через вызов функции query из ObjGraph
class IInterfGraphObj
{
  friend class ::libs::icore::impl::var1::obj::ObjGraph;

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IInterfGraphObj)

  IInterfGraphObj (const IInterfGraphObj& src)            = delete;
  IInterfGraphObj& operator= (const IInterfGraphObj& src) = delete;

  protected:
  /// Конструктор, защищенный, т.к. создание объектов данного типа не предусмотренно
  IInterfGraphObj ()
  {
  }
  /// Деструктор. Закрываем, удалить данный объект можно только через удаления производного
  virtual ~IInterfGraphObj ()
  {
  }
};
}   // namespace libs::core::graph
