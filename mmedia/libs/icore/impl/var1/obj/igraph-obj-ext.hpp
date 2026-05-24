#pragma once
/**
\file       igraph-obj-ext.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj
{
/// Расширенный интерфейс объекта в графе по обработке данных для данной реализации
/// Введен, чтобы избежать ненужных dynamic_cast преобразований типов в реализации
class IGraphNodeExt : public ::libs::core::graph::IGraphNode
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IGraphNodeExt)

  IGraphNodeExt ()
  {
  }

  virtual ~IGraphNodeExt ()
  {
  }

  IGraphNodeExt (const IGraphNodeExt& src)            = delete;
  IGraphNodeExt& operator= (const IGraphNodeExt& src) = delete;

  /// Функция загрузки свойств из xml
  /// \param[in]  root узел xml
  void
  load (const ::pugi::xml_named_node_iterator& root)
  {
    load_int (root);
  }
  /// Функция соединения двух объектов
  /// \param[in]  idpt1  индекс выходной точки соединения данного объекта
  /// \param[in]  next   следующий объект, к которому будет подсоединен данный
  /// \param[in]  idpt2  индекс входной точки следующего объектаю
  void
  connect (std::int32_t idpt1, IGraphNodeExt::ptr& next, std::int32_t idpt2)
  {
    return connect_int (idpt1, next, idpt2);
  }

  private:
  //  IGraphNodeExt interface
  virtual void load_int (const ::pugi::xml_named_node_iterator& root)       = 0;
  virtual void connect_int (int idpt1, IGraphNodeExt::ptr& next, int idpt2) = 0;
};
}   // namespace libs::icore::impl::var1::obj
