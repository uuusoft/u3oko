#pragma once
/**
\file       base-id-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       18.07.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace base_id {
/**
\brief  Свойства фильтра графа обработк данных для идентификации объекта данных.
*/
class BaseIdProp : public ievents::Event
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
  // ext types
  using buff2module_infos_type = std::list<Buff2ModuleInfo>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseIdProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseIdProp);
  UUU_DISABLE_ACOPY_TYPE (BaseIdProp);

  explicit BaseIdProp (const Acessor& = Acessor (0));

  virtual ~BaseIdProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/base_id/base-id-prop";
    return _ret;
  }

  source_name_type       source_name_;       //< Имя источника-объекта (камеры, микрофон и т.п.).
  buff2module_infos_type buff2modules_;      //< Информация о маршрутизации данных от этого источника.


  protected:
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;


  private:
  //  int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  void load_buff2module (const base_functs::xml::itn& _node, Buff2ModuleInfo* _prop);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}      // namespace libs::ievents::props::base_id

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::base_id::BaseIdProp);
