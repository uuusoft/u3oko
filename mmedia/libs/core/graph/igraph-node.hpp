#pragma once
/**
\file       igraph-node.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_core_lib
\brief      Объявление интерфейса объекта графа по обработке данных
*/

namespace libs::core::graph
{
/// Интерфейс объекта в графе по обработке данных
class IGraphNode
{
  friend class ::libs::icore::impl::var1::graph::Graph;
  friend class ::libs::icore::impl::var1::obj::ObjGraph;
  friend class ::libs::icore::impl::var1::obj::IGraphNodeExt;

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (IGraphNode)
  U3_ADD_DELETE_MOVE_COPY (IGraphNode)

  protected:
  /// Функция запроса поддержки интерфейса объектом
  /// \param[in]  id   идентификатор интерфейса
  /// \return     не 0, при успехе
  IInterfGraphObj::raw_ptr
  query (const ::libs::utility::utils::cuuid& id)
  {
    return query_int (id);
  }

  void
  send_event2me (events::IEvent::ptr& evnt)
  {
    send_event2me_int (evnt);
  }

  void
  run ()
  {
    run_int ();
  }

  void
  stop ()
  {
    stop_int ();
  }

  private:
  /// Конструктор, закрытый, базовый класс с чисто виртуальными функциями
  IGraphNode () = default;
  /// Деструктор, закрываем, удалить объект может только сам граф или реализации, а не клиент (пусть и по его требованию)
  virtual ~IGraphNode () = default;

  //  IGraphNode interface
  virtual auto query_int (const ::libs::utility::utils::cuuid&) -> IInterfGraphObj::raw_ptr = 0;
  virtual auto send_event2me_int (events::IEvent::ptr&) -> void                             = 0;
  virtual auto run_int () -> void                                                           = 0;
  virtual auto stop_int () -> void                                                          = 0;
};
}   // namespace libs::core::graph
