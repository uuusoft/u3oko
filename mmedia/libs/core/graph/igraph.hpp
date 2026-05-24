#pragma once
/**
\file       igraph.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_core_lib
\brief      Объявление интерфейса графа обработки данных
*/

namespace libs::core::graph
{
/// Тип для функции-параметра, передающимся при посылки события в граф
using send_func_type = std::function< bool (const NodeID& obj_info, IGraphNode::craw_ptr) >;

/// Интерфейс графа обработки данных. Все функции интерфейса потокобезопасны
class IGraph
{
  friend class ::libs::icore::impl::var1::graph::Graph;

  public:
  //  ext types
  using obj_ids_type = std::set< NodeID >;   //< REFACT unordered_set

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IGraph)

  IGraph (const IGraph& src)            = delete;
  IGraph& operator= (const IGraph& src) = delete;

  /// Функция конструирования графа из xml файла
  void
  load (const std::string& file)
  {
    load_int (file);
  }

  /// Функция получения идентификаторов всех объектов в графе
  const obj_ids_type&
  get_objs ()
  {
    return get_objs_int ();
  }

  /// Функция посылки события в граф его объектам
  void
  send_event2obj (const NodeID& id_obj, events::IEvent::ptr& evnt)
  {
    send_event2obj_int (id_obj, evnt);
  }

  /// Функция установки интерфейса для отправки сообщений в лог системы
  void
  set_logger (::libs::link::ILink::weak_ptr ptr)
  {
    U3_ASSERT (ptr.lock ());
    set_logger_int (ptr);
  }

  private:
  /// Конструктор, закрытый для определенности, т.к базовый класс с чисто виртуальными функциями
  IGraph ()
  {
  }

  /// Деструктор, закрытый, удалить граф может только само ядро
  /// Клиент может только попросить ядро удалить данный граф через сообщение
  virtual ~IGraph ()
  {
  }

  //  IGraph interface
  virtual void                load_int (const std::string& file)                                   = 0;
  virtual const obj_ids_type& get_objs_int ()                                                      = 0;
  virtual void                send_event2obj_int (const NodeID& id_obj, events::IEvent::ptr& evnt) = 0;
  virtual void                set_logger_int (::libs::link::ILink::weak_ptr ptr)                   = 0;
};
}   // namespace libs::core::graph
