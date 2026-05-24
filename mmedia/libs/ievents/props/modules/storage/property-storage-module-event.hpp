#pragma once
/**
\file       property-storage-module-event.hpp
\date       22.07.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::modules::storage
{
/// Хранимые свойства модуля хранения данных
class PropertyStorageModuleEvent : public ievents::Event
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
  virtual ~PropertyStorageModuleEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/modules/storage/property-storage-module-event";
    return ret;
  }

  const paths_type& get_paths () const;
  const Checkers&   get_check () const;

  protected:
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;

  paths_type paths_;   //< Пути для данных
  Checkers   check_;   //< Тип проверки индексирования

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};
}   // namespace libs::ievents::props::modules::storage

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::modules::storage::PropertyStorageModuleEvent);
