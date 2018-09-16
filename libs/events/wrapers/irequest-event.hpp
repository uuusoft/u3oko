//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       irequest-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace libs { namespace events {
/**
\brief  Событие запроса какого либо другого (вложенного в него) события. 
        Используется как флаг запроса (требуется ответ в виде вложенного события).
*/
class IRequestEvent : public IWrapBaseEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IRequestEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (IRequestEvent);
  UUU_DISABLE_ACOPY_TYPE (IRequestEvent);

  explicit IRequestEvent (const Acessor& = Acessor (0), IEvent::ptr _int = IEvent::ptr ());

  virtual ~IRequestEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/events/irequest-event";
    return _ret;
  }


  protected:
  virtual IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void        copy_int (const IEvent::craw_ptr _src) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (IWrapBaseEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}      // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::IRequestEvent);
