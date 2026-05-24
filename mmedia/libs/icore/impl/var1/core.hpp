#pragma once
/**
\file       core.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       22.12.2016
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1
{
/// Локальная (внутрипроцессная) реализация внешнего интерфейса ядра
class Core final : public ::libs::core::ICore
{
  public:
  //  ext types
  using out_wgraphs_type = std::list< ::libs::core::graph::IGraph::weak_ptr >;

  Core ();
  virtual ~Core ();

  private:
  //  internal typess
  using sync_type   = std::mutex;
  using lock_type   = std::lock_guard< sync_type >;
  using graphs_type = std::list< ::libs::core::graph::IGraph::ptr >;

  //  ::libs::core::ICore impl
  virtual ::libs::core::graph::IGraph::weak_ptr create_graph_int () override;
  virtual void                                  get_graphs_int (out_wgraphs_type& graphs) override;
  virtual bool                                  delete_graph_int (::libs::core::graph::IGraph::weak_ptr obj) override;

  /// Функция удаления всех графов обработки данных Ожидается, что при ее вызове никаких клиентов ядра уже не существует
  void delete_graphs ();

  graphs_type graphs_;   //< Все существующие пути ядра
  sync_type   mtx_;      //< Для синхронизации доступа к объекту
};
}   // namespace libs::icore::impl::var1
