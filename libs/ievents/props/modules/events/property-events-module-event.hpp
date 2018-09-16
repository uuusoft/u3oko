//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       property-events-module-event.hpp
\date       09.09.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace modules { namespace events {
/**
\brief  Событие для управления свойствами модуля хранения событий системы.
*/
class PropertyEventsModuleEvent : public ievents::Event
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
  using value_type  = unsigned int;
  //using bounds_type = std::pair<value_type, value_type>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (PropertyEventsModuleEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (PropertyEventsModuleEvent);
  UUU_DISABLE_ACOPY_TYPE (PropertyEventsModuleEvent);

  explicit PropertyEventsModuleEvent (const Acessor& = Acessor (0));

  virtual ~PropertyEventsModuleEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/modules/events/property-events-module-event";
    return _ret;
  }

  value_type get_val (const ValsEventsModule& _key) const;

  void set_val (const ValsEventsModule& _key, value_type _val);


  protected:
  //  int types
  using val_storage_type = ::libs::helpers::utils::ValuesStorage<ValsEventsModule, value_type, UUU_ICAST_INT (ValsEventsModule::max_val)>;
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;

  val_storage_type vals_;      //< Значения полей.


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}}      // namespace libs::ievents::props::modules::log

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::modules::events::PropertyEventsModuleEvent);
