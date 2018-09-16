//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       property-storage-module-event.hpp
\date       22.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace modules { namespace storage {
/**
\brief  Хранимые свойства модуля хранения данных.
*/
class PropertyStorageModuleEvent : public ievents::Event
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
  using paths_type = std::list<PathInfo>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (PropertyStorageModuleEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (PropertyStorageModuleEvent);
  UUU_DISABLE_ACOPY_TYPE (PropertyStorageModuleEvent);

  explicit PropertyStorageModuleEvent (const Acessor& = Acessor (0));

  virtual ~PropertyStorageModuleEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/modules/storage/property-storage-module-event";
    return _ret;
  }

  const paths_type& get_paths () const;

  const CheckerStorageType& get_check () const;


  protected:
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;

  paths_type         paths_;      //< Пути для данных.
  CheckerStorageType check_;      //< Тип проверки индексирования.

  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}}      // namespace libs::ievents::props::modules::storage

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::modules::storage::PropertyStorageModuleEvent);
