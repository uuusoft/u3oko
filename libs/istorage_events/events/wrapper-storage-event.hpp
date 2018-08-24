//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       wrapper-http-event.hpp
\date       21.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/

namespace libs { namespace istorage_events { namespace events {
/**
  \brief  Класс событие для обертки другого события с целью указания модуля-назначения в виде storage сервера.
  */
class WrapperStorageEvent : public BaseStorageEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (WrapperStorageEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (WrapperStorageEvent);
  UUU_DISABLE_ACOPY_TYPE (WrapperStorageEvent);

  explicit WrapperStorageEvent (const Acessor& = Acessor (0), ::libs::events::IEvent::ptr _msg = ::libs::events::IEvent::ptr ());

  virtual ~WrapperStorageEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/istorage_events/events/wrapper-storage-event";
    return _ret;
  }

  ::libs::events::IEvent::ptr get_msg () const;

  void set_msg (::libs::events::IEvent::ptr&);


  protected:
  ::libs::events::IEvent::ptr int_;      //< событие, для которого производится синхронизация.


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseStorageEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::WrapperStorageEvent);
