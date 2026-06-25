#pragma once
/**
\file       add-event2base.hpp
\author     Erashov Anton erashov2026@proton.me
\date       09.09.2018
\project    u3_ievents_lib
*/

namespace libs::ievents_events::events
{
class AddEvent2Base : public BaseEventsEvent
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
  using object_id_type  = std::string;
  using machine_id_type = ::libs::helpers::utils::cuuid;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (AddEvent2Base)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (AddEvent2Base)
  U3_HELPER_DISABLE_ACOPY_TYPE (AddEvent2Base)

  explicit AddEvent2Base (
    const Acessor&                                = Acessor (0),
    const ::libs::events::IEvent::ptr& obj        = ::libs::events::IEvent::ptr (),
    const machine_id_type&             machine_id = machine_id_type (),
    const object_id_type&              object_id  = object_id_type ());

  virtual ~AddEvent2Base () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents_events/events/add-event2base";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto sync_event_props (const machine_id_type&, const object_id_type&) -> void;
  auto set_event (::libs::events::IEvent::ptr& obj) -> void;
  auto get_event () const -> ::libs::events::IEvent::ptr;
  auto set_object_id (const object_id_type& id) -> void;
  auto get_object_id () const -> const object_id_type&;
  auto set_machine_id (const machine_id_type& id) -> void;
  auto get_machine_id () const -> const machine_id_type&;

  private:
  //  internal typess
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (BaseEventsEvent)

  machine_id_type             machine_id_;   //<
  object_id_type              object_id_;    //<
  ::libs::events::IEvent::ptr add_event_;    //<

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

BOOST_CLASS_EXPORT_KEY (::libs::ievents_events::events::AddEvent2Base);
