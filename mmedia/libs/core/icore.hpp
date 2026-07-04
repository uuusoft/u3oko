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
  U3_ADD_POINTERS_TO_SELF (ICore)
  U3_ADD_DELETE_MOVE_COPY (ICore)

  virtual ~ICore () = default;

  auto
  create_graph () -> graph::IGraph::weak_ptr
  {
    return create_graph_int ();
  }

  auto
  delete_graph (graph::IGraph::weak_ptr obj) -> bool
  {
    return delete_graph_int (obj);
  }

  auto
  get_graphs (std::list< graph::IGraph::weak_ptr >& graphs) -> void
  {
    return get_graphs_int (graphs);
  }

  protected:
  /// Закрытый конструктор, т.к. это базовый класс и его экземпляры не могут существовать
  ICore () = default;

  private:
  //  ICore interface
  virtual auto create_graph_int () -> graph::IGraph::weak_ptr                 = 0;
  virtual auto get_graphs_int (std::list< graph::IGraph::weak_ptr >&) -> void = 0;
  virtual auto delete_graph_int (graph::IGraph::weak_ptr) -> bool             = 0;
};
}   // namespace libs::core
