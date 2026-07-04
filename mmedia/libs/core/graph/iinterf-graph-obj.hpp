#pragma once
/**
\file       iinterf-graph-obj.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
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
  U3_ADD_POINTERS_TO_SELF (IInterfGraphObj)
  U3_ADD_DELETE_MOVE_COPY (IInterfGraphObj)

  protected:
  /// Конструктор, закрываем, т.к. создание объектов данного типа не предусмотренно
  IInterfGraphObj () = default;
  /// Деструктор. Закрываем, удалить данный объект можно только через удаления производного
  virtual ~IInterfGraphObj () = default;
};
}   // namespace libs::core::graph
