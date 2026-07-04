#pragma once
/**
\file       property-log-module-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::modules::log
{
/// Хранимые свойства модуля логирования
class PropertyLogModuleEvent final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using value_type  = std::uint32_t;
  using bounds_type = std::pair< value_type, value_type >;

  U3_ADD_POINTERS_TO_SELF (PropertyLogModuleEvent)
  U3_ADD_MAKE_SHARED_THIS (PropertyLogModuleEvent)
  U3_ADD_DELETE_MOVE_COPY (PropertyLogModuleEvent)

  explicit PropertyLogModuleEvent (const Acessor& = Acessor (0));
  virtual ~PropertyLogModuleEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/props/modules/log/property-log-module-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  value_type get_val (const LogVals& key) const;
  void       set_val (const LogVals& key, value_type val);
  void       correct ();

  protected:
  //  internal typess
  using val_storage_type = ::libs::utility::utils::ValuesStorage< LogVals, value_type, LogVals::max_val, 0u >;

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  val_storage_type vals_;   //< Значения полей

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events_base::props::modules::log

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::modules::log::PropertyLogModuleEvent);
