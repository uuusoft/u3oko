#pragma once
/**
\file       property-events-module-event.hpp
\date       09.09.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::modules::events
{
class PropertyEventsModuleEvent final : public ievents::Event
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
  using value_type = std::uint32_t;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (PropertyEventsModuleEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (PropertyEventsModuleEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (PropertyEventsModuleEvent)

  explicit PropertyEventsModuleEvent (const Acessor& = Acessor (0));
  virtual ~PropertyEventsModuleEvent () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/modules/events/property-events-module-event";
    return ret;
  }

  value_type get_val (const EventsVals& key) const;
  void       set_val (const EventsVals& key, value_type val);

  protected:
  //  internal typess
  using val_storage_type = ::libs::helpers::utils::ValuesStorage< EventsVals, value_type, EventsVals::max_val, 0u >;

  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;

  val_storage_type vals_;   //<

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::ievents::props::modules::events

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::modules::events::PropertyEventsModuleEvent);
