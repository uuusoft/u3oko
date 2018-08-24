//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       property-log-module-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace modules { namespace log {
/**
  \brief  empty brief
  */
class PropertyLogModuleEvent : public ievents::Event
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
  using bounds_type = std::pair<value_type, value_type>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (PropertyLogModuleEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (PropertyLogModuleEvent);
  UUU_DISABLE_ACOPY_TYPE (PropertyLogModuleEvent);

  explicit PropertyLogModuleEvent (const Acessor& = Acessor (0));

  virtual ~PropertyLogModuleEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/modules/log/property-log-module-event";
    return _ret;
  }

  value_type get_val (const ValsLogModule& _key) const;

  void set_val (const ValsLogModule& _key, value_type _val);

  void correct ();


  protected:
  //  int types
  using val_storage_type = ::libs::helpers::utils::ValuesStorage<ValsLogModule, value_type, UUU_ICAST_INT (ValsLogModule::max_val)>;

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
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

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::modules::log::PropertyLogModuleEvent);
