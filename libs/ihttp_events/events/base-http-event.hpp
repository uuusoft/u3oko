#pragma once
/**
\file       base-http-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ihttp_events
\brief      empty brief
*/

namespace libs { namespace ihttp_events { namespace events {
/**
  \brief  Базовый класс для событий подсистемы "http сервер".
  */
class BaseHttpEvent : public ::libs::ievents::TimedEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseHttpEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseHttpEvent);
  UUU_DISABLE_ACOPY_TYPE (BaseHttpEvent);

  BaseHttpEvent (const Acessor& = Acessor (0));

  virtual ~BaseHttpEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ihttp_events/events/base-http-event";
    return _ret;
  }


  protected:
  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
};

}}}      // namespace libs::ihttp_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ihttp_events::events::BaseHttpEvent);
