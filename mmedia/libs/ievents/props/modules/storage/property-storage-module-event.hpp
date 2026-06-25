#pragma once
/**
\file       property-storage-module-event.hpp
\date       22.07.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::props::modules::storage
{
/// Хранимые свойства модуля хранения данных
class PropertyStorageModuleEvent : virtual public ievents::Event
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
  using paths_type = std::vector< PathInfo >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (PropertyStorageModuleEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (PropertyStorageModuleEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (PropertyStorageModuleEvent)

  explicit PropertyStorageModuleEvent (const Acessor& = Acessor (0));
  virtual ~PropertyStorageModuleEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/modules/storage/property-storage-module-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  const paths_type& get_paths () const;
  const Checkers&   get_check () const;

  protected:
  //  ievents::Event overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  paths_type paths_;   //< Пути для данных
  Checkers   check_;   //< Тип проверки индексирования

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::ievents::props::modules::storage

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::modules::storage::PropertyStorageModuleEvent);
