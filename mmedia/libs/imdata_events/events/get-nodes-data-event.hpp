#pragma once
/**
\file       get-nodes-data-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_imdata_events
*/

namespace libs::imdata_events::events
{
/// Событие возвращает список узлов указанного графа обработки данных
class GetNodesDataEvent : public BaseNodesDataEvent
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
  using node_type       = NodeGraphInfo;
  using nodes_list_type = std::list< node_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (GetNodesDataEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GetNodesDataEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (GetNodesDataEvent)

  explicit GetNodesDataEvent (
    const Acessor&                  = Acessor (0),
    const id_graph_type&   id_graph = "",
    const nodes_list_type& nodes    = nodes_list_type ());

  virtual ~GetNodesDataEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/imdata_events/events/get-nodes-data-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  const nodes_list_type& get_nodes () const;
  void                   set_nodes (nodes_list_type& nodes);
  bool                   check () const;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::imdata_events::events::BaseNodesDataEvent)

  nodes_list_type nodes_;   //< Списк узлов в графе обработки данных

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  //  BaseNodesDataEvent overrides
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::GetNodesDataEvent);
