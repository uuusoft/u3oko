#pragma once
/**
\file       base-events-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents_events { namespace events {
/**
\brief  Базовый класс для событий подсистемы "события".
*/
class BaseEventsEvent : public ::libs::ievents::TimedEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseEventsEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseEventsEvent);
  UUU_DISABLE_ACOPY_TYPE (BaseEventsEvent);

  BaseEventsEvent (const Acessor& = Acessor (0));

  virtual ~BaseEventsEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents_events/events/base-events-event";
    return _ret;
  }


  protected:
  //  ievents::Event overrides
  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
  //  ievents::Event overrides
  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
};

}}}      // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ievents_events::events::BaseEventsEvent);
