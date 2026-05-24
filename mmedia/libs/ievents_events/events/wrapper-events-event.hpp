#pragma once
/**
\file       wrapper-events-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents_events::events
{
/// Класс событие для обертки другого события с целью указания модуля-назначения в виде сервера событий
class WrapperEventsEvent : public BaseEventsEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (WrapperEventsEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (WrapperEventsEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (WrapperEventsEvent)

  explicit WrapperEventsEvent (const Acessor& = Acessor (0), ::libs::events::IEvent::ptr msg = ::libs::events::IEvent::ptr ());
  virtual ~WrapperEventsEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents_events/events/wrapper-events-event";
    return ret;
  }

  ::libs::events::IEvent::ptr get_msg () const;
  void                        set_msg (::libs::events::IEvent::ptr&);

  protected:
  ::libs::events::IEvent::ptr int_;   //< Событие, которое требуется передать в подсистему

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ievents_events::events::WrapperEventsEvent);
