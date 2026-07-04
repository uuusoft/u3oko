#pragma once
/**
\file       update-listener-events-msg.hpp
\author     Erashov Anton erashov2026@proton.me
\date       17.09.2018
\project    u3_events_base_lib
*/

namespace libs::events_msg::events
{
enum class SubscribeActions : std::uint32_t
{
  enable  = 0x00,   //<
  disable = 0x01,   //<
  unknown = 0xFF    //<
};

auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value&, const SubscribeActions&) -> void;
auto tag_invoke (::boost::json::value_to_tag< SubscribeActions >, const ::boost::json::value&) -> SubscribeActions;

class UpdateListenerEventsMsg : public BaseEventsMsg
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  using listener_id_type  = std::string;
  using hids_storage_type = std::vector< std::string >;

  U3_ADD_POINTERS_TO_SELF (UpdateListenerEventsMsg)
  U3_ADD_MAKE_SHARED_THIS (UpdateListenerEventsMsg)
  U3_ADD_DELETE_MOVE_COPY (UpdateListenerEventsMsg)

  UpdateListenerEventsMsg (
    const Acessor&          = Acessor (0),
    listener_id_type        = "",
    hids_storage_type       = hids_storage_type (),
    const SubscribeActions& = SubscribeActions::enable);

  virtual ~UpdateListenerEventsMsg () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_msg/events/update-listener-events-msg";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto set_listener_id (const listener_id_type& id) -> void;
  auto get_listener_id () const -> const listener_id_type&;
  auto set_event_types (const hids_storage_type& event_types) -> void;
  auto get_event_types () const -> const hids_storage_type&;
  auto set_action (const SubscribeActions& id) -> void;
  auto get_action () const -> const SubscribeActions&;

  private:
  //  internal typess
  U3_ADD_SUPER_CLASS (BaseEventsMsg)

  listener_id_type  listener_id_;   //<
  hids_storage_type event_types_;   //<
  SubscribeActions  action_;        //<

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
}   // namespace libs::events_msg::events

BOOST_CLASS_EXPORT_KEY (::libs::events_msg::events::UpdateListenerEventsMsg);
