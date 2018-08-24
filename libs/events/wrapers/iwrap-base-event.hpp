//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       iwrap-base-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace libs { namespace events {
/**
  \brief  Событие синхронизации. 
          Используется как флаг синхронности (требуется ответ на вложенное событие).
  */
class IWrapBaseEvent : public IEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IWrapBaseEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (IWrapBaseEvent);
  UUU_DISABLE_ACOPY_TYPE (IWrapBaseEvent);

  explicit IWrapBaseEvent (const Acessor& = Acessor (0), IEvent::ptr _int = IEvent::ptr ());

  virtual ~IWrapBaseEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/events/iwrap-base-event";
    return _ret;
  }

  IEvent::ptr get_msg () const;

  void set_msg (IEvent::ptr&);


  protected:
  IEvent::ptr int_;      //< Событие, для которого производится синхронизация.

  virtual IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual bool        check_node_int (const base_functs::xml::itn& _node) override;
  virtual void        load_int (const base_functs::xml::itn& _prop) override;
  virtual void        copy_int (const IEvent::craw_ptr _src) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (IEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}      // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::IWrapBaseEvent);
