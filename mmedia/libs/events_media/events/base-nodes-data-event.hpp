#pragma once
/**
\file       base-nodes-data-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_media
*/

namespace libs::events_media::events
{
/// Базовое события для событий работы с узлами пути обработки данных
class BaseNodesDataEvent : public BaseDataEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using node_type       = NodeGraphInfo;
  using nodes_list_type = std::list< node_type >;
  using id_graph_type   = ChangeGraphsDataEvent::id_folder_type;

  U3_ADD_POINTERS_TO_SELF (BaseNodesDataEvent)
  U3_ADD_MAKE_SHARED_THIS (BaseNodesDataEvent)
  U3_ADD_DELETE_MOVE_COPY (BaseNodesDataEvent)

  explicit BaseNodesDataEvent (const Acessor& = Acessor (0), id_graph_type id_graph = id_graph_type ());
  virtual ~BaseNodesDataEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_media/events/base-nodes-data-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  const id_graph_type& get_id_graph () const;
  void                 set_id_graph (id_graph_type&& id);
  bool                 check () const;

  protected:
  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_media::events::BaseDataEvent)

  id_graph_type id_graph_;   //< Идентификатор графа, с узлами которого требуется работать

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::events_media::events

BOOST_CLASS_EXPORT_KEY (::libs::events_media::events::BaseNodesDataEvent);
