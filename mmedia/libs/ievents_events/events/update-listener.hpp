#pragma once
/**
\file       update-listener.hpp
\author     Erashov Anton erashov2026@proton.me
\date       17.09.2018
\project    u3_ievents_lib
*/

namespace libs::ievents_events::events
{
enum class SubscribeActions : std::uint32_t
{
  enable  = 0x00,   //<
  disable = 0x01,   //<
  unknown = 0xFF    //<
};

void             tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const SubscribeActions& src);
SubscribeActions tag_invoke (::boost::json::value_to_tag< SubscribeActions >, const ::boost::json::value& jvs);

class UpdateListener : public BaseEventsEvent
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
  using listener_id_type  = std::string;
  using hids_storage_type = std::vector< std::string >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (UpdateListener)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (UpdateListener)
  U3_HELPER_DISABLE_ACOPY_TYPE (UpdateListener)

  UpdateListener (
    const Acessor&           = Acessor (0),
    const listener_id_type&  = "",
    const hids_storage_type& = hids_storage_type (),
    const SubscribeActions&  = SubscribeActions::enable);

  virtual ~UpdateListener () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents_events/events/update-listener";
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
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (BaseEventsEvent)

  listener_id_type  listener_id_;   //<
  hids_storage_type event_types_;   //<
  SubscribeActions  action_;        //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ievents_events::events::UpdateListener);
