#pragma once
/**
\file       igraph-node.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IGraphNode)

  IGraphNode (const IGraphNode& src)            = delete;
  IGraphNode& operator= (const IGraphNode& src) = delete;

  protected:
  /// Функция запроса поддержки интерфейса объектом
  /// \param[in]  id   идентификатор интерфейса
  /// \return     не 0, при успехе
  IInterfGraphObj::raw_ptr
  query (const ::libs::helpers::utils::cuuid& id)
  {
    return query_int (id);
  }

  /// Функция посылки события в граф
  void
  send_event2me (events::IEvent::ptr& evnt)
  {
    send_event2me_int (evnt);
  }

  /// Функция запуска объекта
  void
  run ()
  {
    run_int ();
  }

  /// Функция остановки объекта
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
  virtual IInterfGraphObj::raw_ptr query_int (const ::libs::helpers::utils::cuuid& id) = 0;
  virtual void                     send_event2me_int (events::IEvent::ptr& evnt)       = 0;
  virtual void                     run_int ()                                          = 0;
  virtual void                     stop_int ()                                         = 0;
};
}   // namespace libs::core::graph
