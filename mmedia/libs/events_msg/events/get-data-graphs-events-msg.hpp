#pragma once
/**
\file       get-data-graphs-events-msg.hpp
\author     Erashov Anton erashov2026@proton.me
\date       05.06.2022
\project    u3_events_base_lib
*/

namespace libs::events_msg::events
{
class GetDataGraphsEventsMsg : public BaseEventsMsg
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  using id_graph_type          = std::string;
  using id_graphs_storage_type = std::vector< id_graph_type >;

  U3_ADD_POINTERS_TO_SELF (GetDataGraphsEventsMsg)
  U3_ADD_MAKE_SHARED_THIS (GetDataGraphsEventsMsg)
  U3_ADD_DELETE_MOVE_COPY (GetDataGraphsEventsMsg)

  GetDataGraphsEventsMsg (const Acessor& = Acessor (0));
  virtual ~GetDataGraphsEventsMsg ();

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_msg/events/get-data-graphs-events-msg";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto set_data_graphs (id_graphs_storage_type&& events) -> void;
  auto get_data_graphs () const -> const id_graphs_storage_type&;

  private:
  //  internal typess
  U3_ADD_SUPER_CLASS (BaseEventsMsg)

  id_graphs_storage_type data_graph_ids_;   //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_msg::events

BOOST_CLASS_EXPORT_KEY (::libs::events_msg::events::GetDataGraphsEventsMsg);
