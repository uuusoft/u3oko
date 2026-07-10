#pragma once
/**
\file       property-storage-module-event.hpp
\date       22.07.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::modules::storage
{
/// Хранимые свойства модуля хранения данных
class PropertyStorageModuleEvent : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using paths_type = std::vector< PathInfo >;

  U3_ADD_POINTERS_TO_SELF (PropertyStorageModuleEvent)
  U3_ADD_MAKE_SHARED_THIS (PropertyStorageModuleEvent)
  U3_ADD_DELETE_MOVE_COPY (PropertyStorageModuleEvent)

  explicit PropertyStorageModuleEvent (const Acessor& = Acessor (0));
  virtual ~PropertyStorageModuleEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/props/modules/storage/property-storage-module-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  const paths_type& get_paths () const;
  const Checkers&   get_check () const;

  protected:
  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  paths_type paths_;   //< Пути для данных
  Checkers   check_;   //< Тип проверки индексирования

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events_base::props::modules::storage

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::modules::storage::PropertyStorageModuleEvent);
