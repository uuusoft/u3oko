#pragma once
/**
\file       add-event2base.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents_events/events/add-event2base";
    return ret;
  }

  void                        sync_event_props (const machine_id_type&, const object_id_type&);
  void                        set_event (::libs::events::IEvent::ptr& obj);
  ::libs::events::IEvent::ptr get_event () const;
  void                        set_object_id (const object_id_type& id);
  const object_id_type&       get_object_id () const;
  void                        set_machine_id (const machine_id_type& id);
  const machine_id_type&      get_machine_id () const;

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
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ievents_events::events::AddEvent2Base);
