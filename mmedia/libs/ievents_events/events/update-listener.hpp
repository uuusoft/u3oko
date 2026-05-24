#pragma once
/**
\file       update-listener.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

void             tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const SubscribeActions& src);
SubscribeActions tag_invoke (::boost::json::value_to_tag< SubscribeActions >, const ::boost::json::value& jv);

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
  using hids_storage_type = std::vector< IEvent::hid_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (UpdateListener)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (UpdateListener)
  U3_HELPER_DISABLE_ACOPY_TYPE (UpdateListener)

  UpdateListener (
    const Acessor&           = Acessor (0),
    const listener_id_type&  = "",
    const hids_storage_type& = hids_storage_type (),
    const SubscribeActions&  = SubscribeActions::enable);

  virtual ~UpdateListener ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents_events/events/update-listener";
    return ret;
  }

  void                     set_listener_id (const listener_id_type& id);
  const listener_id_type&  get_listener_id () const;
  void                     set_event_types (const hids_storage_type& event_types);
  const hids_storage_type& get_event_types () const;
  void                     set_action (const SubscribeActions& id);
  const SubscribeActions&  get_action () const;

  private:
  //  internal typess
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (BaseEventsEvent)

  listener_id_type  listener_id_;   //<
  hids_storage_type event_types_;   //<
  SubscribeActions  action_;        //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ievents_events::events::UpdateListener);
