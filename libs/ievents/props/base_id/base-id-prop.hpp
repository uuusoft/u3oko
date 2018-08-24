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
// syn
using id_link_module_type = std::string;
using source_name_type    = std::string;
/**
  \brief  Информация, каким образом и куда передавать конкретный буфер с данными.
  */
struct Buff2ModuleInfo
{
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (Buff2ModuleInfo);

  Buff2ModuleInfo () :
    fps_ (0.0f),
    indx_buff_ (::utils::dbuffs::video::consts::offs::invalid)
  {}

  float               fps_;            //< Частота передачи данных. 0 - не лимитируется.
  off_buff_type       indx_buff_;      //< Индекс буфера-источника.
  id_link_module_type module_;         //< Идентификатор модуля, в который требуется передать данный буфер.

  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (fps_);
    ar& BOOST_SERIALIZATION_NVP (indx_buff_);
    ar& BOOST_SERIALIZATION_NVP (module_);
    return;
  }
};
/**
  \brief  empty brief
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

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/base_id/base-id-prop";
    return _ret;
  }

  source_name_type       source_name_;       //< Имя источника (камеры, микрофон и т.п.)
  buff2module_infos_type buff2modules_;      //< Информация о маршрутизации данных от источника.


  protected:
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
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
