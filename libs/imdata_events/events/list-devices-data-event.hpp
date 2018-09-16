//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       list-devices-data-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      Объявление интерфейса события для обработки списка устройств системы.
*/

namespace libs { namespace imdata_events { namespace events {
/**
\brief  Событие содержит в себе список устройств захвата данных в системе.
*/
class ListDevicesDataEvent : public BaseDataEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };


  public:
  //  ext types
  using device_type        = std::string;
  using devices_type       = std::list<device_type>;
  using devices_group_type = std::string;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ListDevicesDataEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ListDevicesDataEvent);
  UUU_DISABLE_ACOPY_TYPE (ListDevicesDataEvent);

  explicit ListDevicesDataEvent (const Acessor& = Acessor (0), const devices_group_type& _group = "", const devices_type& _devices = devices_type ());

  virtual ~ListDevicesDataEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/imdata_events/events/list-devices-data-event";
    return _ret;
  }

  const ListDevicesDataEvent::devices_group_type& get_group () const;

  void set_group (ListDevicesDataEvent::devices_group_type&& _src);

  const ListDevicesDataEvent::devices_type& get_devices () const;

  void set_devices (ListDevicesDataEvent::devices_type&& _src);


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseDataEvent);

  devices_group_type group_;        //< Идентификатор группы устройств. Системно зависимое значение. Для примера значений: directshow, direct etc.
  devices_type       devices_;      //< Список устройств.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual void                        load_int (const base_functs::xml::itn& _prop) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::ListDevicesDataEvent);
