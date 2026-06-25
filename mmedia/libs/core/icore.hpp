#pragma once
/**
\file       icore.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_core_lib
\brief      Объявление интерфейса ядра по обработки данных
*/

/// Пространство имен для ядра для обработки данных
namespace libs::core
{
/// Интерфейс ядра по обработки данных
/// Все функции открытого интерфейса должны быть потокобезопасны
class ICore
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ICore)

  virtual ~ICore () = default;

  /// Функция создания графа обработки данных
  /// Созданный граф требует явного удаления через функцию delete_graph
  graph::IGraph::weak_ptr
  create_graph ()
  {
    return create_graph_int ();
  }

  /// Функция получения существующих графов обработки данных ядра
  void
  get_graphs (std::list< graph::IGraph::weak_ptr >& graphs)
  {
    return get_graphs_int (graphs);
  }

  bool
  delete_graph (graph::IGraph::weak_ptr obj)
  {
    return delete_graph_int (obj);
  }

  protected:
  /// Закрытый конструктор, т.к. это базовый класс и его экземпляры не могут существовать
  ICore () = default;

  private:
  //  ICore interface
  virtual graph::IGraph::weak_ptr create_graph_int ()                                           = 0;
  virtual void                    get_graphs_int (std::list< graph::IGraph::weak_ptr >& graphs) = 0;
  virtual bool                    delete_graph_int (graph::IGraph::weak_ptr obj)                = 0;
};
}   // namespace libs::core
