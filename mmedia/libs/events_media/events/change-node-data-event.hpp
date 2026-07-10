#pragma once
/**
\file       change-node-data-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_media
*/

namespace libs::events_media::events
{
/// Событие производит указанное действие над указаним списком xml файлов для графов обработки данных
class ChangeNodeDataEvent : public BaseNodesDataEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using id_graph_type      = std::string;
  using id_node_graph_type = ::libs::core::graph::NodeID;
  using events_list_type   = std::list< IEvent::ptr >;

  U3_ADD_POINTERS_TO_SELF (ChangeNodeDataEvent)
  U3_ADD_MAKE_SHARED_THIS (ChangeNodeDataEvent)
  U3_ADD_DELETE_MOVE_COPY (ChangeNodeDataEvent)

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
    events_list_type          events   = events_list_type ());

  virtual ~ChangeNodeDataEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_media/events/change-node-data-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_node () const -> const id_node_graph_type&;
  auto set_node (const id_node_graph_type& graph) -> void;
  auto get_action () const -> GraphNodeActions;
  auto set_action (const GraphNodeActions& action) -> void;
  auto get_events () const -> const events_list_type&;
  auto set_events (const events_list_type& action) -> void;
  auto check () const -> bool;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_media::events::BaseNodesDataEvent)

  id_node_graph_type id_node_;   //< Идентификатор узла графа
  GraphNodeActions   action_;    //< Действие, которое требуется произвести со списком событий узлу Установить/Получить/etc
  events_list_type   events_;    //< События-свойства узла графа Используется список например для быстрого получения всех свойств указанного узла

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_media::events

BOOST_CLASS_EXPORT_KEY (::libs::events_media::events::ChangeNodeDataEvent);
