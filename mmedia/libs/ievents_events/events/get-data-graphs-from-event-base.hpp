#pragma once
/**
\file       get-data-graphs-from-event-base.hpp
\author     Erashov Anton erashov2026@proton.me
\date       05.06.2022
\project    u3_ievents_lib
*/

namespace libs::ievents_events::events
{
class GetDataGraphsFromEventBase : public BaseEventsEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  using id_graph_type          = std::string;
  using id_graphs_storage_type = std::vector< id_graph_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (GetDataGraphsFromEventBase)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GetDataGraphsFromEventBase)
  U3_HELPER_DISABLE_ACOPY_TYPE (GetDataGraphsFromEventBase)

  GetDataGraphsFromEventBase (const Acessor& = Acessor (0));
  virtual ~GetDataGraphsFromEventBase ();

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents_events/events/get-data-graphs-from-event-base";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto set_data_graphs (id_graphs_storage_type&& events) -> void;
  auto get_data_graphs () const -> const id_graphs_storage_type&;

  private:
  //  internal typess
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (BaseEventsEvent)

  id_graphs_storage_type data_graph_ids_;   //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ievents_events::events::GetDataGraphsFromEventBase);
