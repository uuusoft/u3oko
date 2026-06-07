#pragma once
/**
\file       change-node-data-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/

namespace libs::imdata_events::events
{
/// Событие производит указанное действие над указаним списком xml файлов для графов обработки данных
class ChangeNodeDataEvent : public BaseNodesDataEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using id_graph_type      = std::string;
  using id_node_graph_type = ::libs::core::graph::NodeID;
  using events_list_type   = std::list< IEvent::ptr >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ChangeNodeDataEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ChangeNodeDataEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ChangeNodeDataEvent)

  /// Рабочий конструктор
  /// \param[in]      action   действие, которое надо произвести над событиями узла графа
  /// \param[in]      id_graph  идентфикатор графа
  /// \param[in]      id_node  идентфикатор узла в графе
  /// \param[in, out] events   события
  explicit ChangeNodeDataEvent (
    const Acessor&            ph       = Acessor (0),
    const GraphNodeActions&   action   = GraphNodeActions::get,
    const id_graph_type&      id_graph = "",
    const id_node_graph_type& id_node  = id_node_graph_type (),
    const events_list_type&   events   = events_list_type ());

  virtual ~ChangeNodeDataEvent () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/imdata_events/events/change-node-data-event";
    return ret;
  }

  const id_node_graph_type& get_node () const;
  void                      set_node (const id_node_graph_type& graph);
  GraphNodeActions          get_action () const;
  void                      set_action (const GraphNodeActions& action);
  const events_list_type&   get_events () const;
  void                      set_events (const events_list_type& action);
  bool                      check () const;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::imdata_events::events::BaseNodesDataEvent)

  id_node_graph_type id_node_;   //< Идентификатор узла графа
  GraphNodeActions   action_;    //< Действие, которое требуется произвести со списком событий узлу Установить/Получить/etc
  events_list_type   events_;    //< События-свойства узла графа Используется список например для быстрого получения всех свойств указанного узла

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::ChangeNodeDataEvent);
