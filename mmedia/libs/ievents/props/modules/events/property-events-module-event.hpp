#pragma once
/**
\file       property-events-module-event.hpp
\date       09.09.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::props::modules::events
{
class PropertyEventsModuleEvent final : virtual public ievents::Event
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

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/modules/events/property-events-module-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  value_type get_val (const EventsVals& key) const;
  void       set_val (const EventsVals& key, value_type val);

  protected:
  //  internal typess
  using val_storage_type = ::libs::helpers::utils::ValuesStorage< EventsVals, value_type, EventsVals::max_val, 0u >;

  //  ievents::Event overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

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
