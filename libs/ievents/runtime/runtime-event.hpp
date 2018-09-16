#pragma once
/**
\file       runtime-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/

namespace libs { namespace ievents { namespace runtime {
/**
\brief  Базовый класс всех событий системы с временной меткой.
*/
class RuntimeEvent : public ievents::TimedEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (RuntimeEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (RuntimeEvent);
  UUU_DISABLE_ACOPY_TYPE (RuntimeEvent);

  explicit RuntimeEvent (const Acessor& = Acessor (0));

  virtual ~RuntimeEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/runtime/runtime-event";
    return _ret;
  }


  protected:
  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::TimedEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
  //  ievents::TimedEvent overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  //virtual void load_int( const base_functs::xml::itn& _node ) override;
};

}}}      // namespace libs::ievents::runtime

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::RuntimeEvent);
