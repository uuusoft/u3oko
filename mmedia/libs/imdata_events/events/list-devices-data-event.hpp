
#pragma once
/**
\file       list-devices-data-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
\brief      Объявление интерфейса события для обработки списка устройств системы
*/

namespace libs::imdata_events::events
{
/// Перечисление доступных типов данных от устройств
enum class DataSources : std::uint32_t
{
  video   = 0x00,   //<  Видео данные
  audio   = 0x01,   //<  Аудио данные
  event   = 0x02,   //<  События данные
  unknown = 0xFF    //<  Не определенно
};

///  Информация о данных устройства
struct DataSourceInfo final {
  public:
  DataSourceInfo (
    const std::string& name      = "",
    const DataSources& type      = DataSources::unknown,
    std::int32_t       max_count = 1,
    std::int32_t       number    = 1);

  virtual ~DataSourceInfo () = default;

  std::string  name_;        //< Имя источника данных
  DataSources  type_;        //< Тип источника данных
  std::int32_t max_count_;   //< Максимальное количество источников данных с данным именем 0 - не ограниченно
  std::int32_t number_;      //< Номер источника данных

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

/// Событие содержит в себе список устройств захвата данных в системе
class ListDevicesDataEvent : public BaseDataEvent
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
  using src_infos_type    = std::vector< DataSourceInfo >;
  using src_devinfos_type = std::vector< src_infos_type >;
  using src_name_type     = std::string;
  using src_names_type    = std::vector< src_name_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ListDevicesDataEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ListDevicesDataEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ListDevicesDataEvent)

  explicit ListDevicesDataEvent (
    const Acessor&                   = Acessor (0),
    const src_names_type&    group   = src_names_type (),
    const src_devinfos_type& devices = src_devinfos_type ());

  virtual ~ListDevicesDataEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/imdata_events/events/list-devices-data-event";
    return ret;
  }

  const ListDevicesDataEvent::src_names_type& get_source_dll_names () const;
  void                                        set_source_dll_names (ListDevicesDataEvent::src_names_type&& src);
  const ListDevicesDataEvent::src_infos_type& get_devices_for_dll (std::size_t indx) const;
  void                                        set_devices_for_dll (std::size_t indx, ListDevicesDataEvent::src_infos_type&& src);

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::imdata_events::events::BaseDataEvent)

  src_names_type    source_dll_names_;   //< Идентификаторы групп устройств. Системно зависимое значение. Для примера значений: directshow, direct etc
  src_devinfos_type dlls_devices_;       //< Список устройств для каждой группы

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::DataSourceInfo);
BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::ListDevicesDataEvent);
