#pragma once
/**
\file       wrapper-log-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilog_events
*/

namespace libs::ilog_events::events
{
/// Класс событие для обертки другого события с целью указания модуля-назначения в виде http сервера
class WrapperLogEvent final : public BaseLogEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (WrapperLogEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (WrapperLogEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (WrapperLogEvent)

  explicit WrapperLogEvent (
    const Acessor&              = Acessor (0),
    ::libs::events::IEvent::ptr = ::libs::events::IEvent::ptr ());

  virtual ~WrapperLogEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ilog_events/events/wrapper-log-event";
    return ret;
  }

  ::libs::events::IEvent::ptr get_msg () const;
  void                        set_msg (::libs::events::IEvent::ptr&);

  protected:
  ::libs::events::IEvent::ptr int_;   //< Событие, для которого производится синхронизация

  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent)

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::WrapperLogEvent);
