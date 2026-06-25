#pragma once
/**
\file       wrapper-log-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
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

  virtual ~WrapperLogEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ilog_events/events/wrapper-log-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_msg () const -> ::libs::events::IEvent::ptr;
  auto set_msg (::libs::events::IEvent::ptr&) -> void;

  protected:
  ::libs::events::IEvent::ptr int_;   //< Событие, для которого производится синхронизация

  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent)

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  //  ievents::Event overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::WrapperLogEvent);
