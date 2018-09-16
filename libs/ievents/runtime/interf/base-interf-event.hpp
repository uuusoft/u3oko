//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       base-interf-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
*/

namespace libs { namespace ievents { namespace runtime { namespace interf {
/**
\brief  Базовое интерфейсное сообщение.
*/
class BaseInterfEvent : public RuntimeEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseInterfEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseInterfEvent);
  UUU_DISABLE_ACOPY_TYPE (BaseInterfEvent);

  explicit BaseInterfEvent (const Acessor& = Acessor (0));

  virtual ~BaseInterfEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/runtime/interf/base-interf-event";
    return _ret;
  }

  void set_active (bool _enable);

  bool is_active () const;

  void set_available( bool _enable);

  bool is_available() const;


  protected:
  //  ievents::Event overrides
  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  //  int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent);

  bool active_;         //< Флаг активности интерфейса.
  bool available_;      //< Флаг наличия в данный момент возможности работы с интерфейсом. Т.е. при его сбросе флаг активности перестает учитываться.
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  //virtual void load_int( const base_functs::xml::itn& _node ) override;
};

}}}}      // namespace libs::ievents::runtime::interf

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::interf::BaseInterfEvent);
