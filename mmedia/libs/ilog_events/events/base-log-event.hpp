#pragma once
/**
\file       base-log-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ilog_events
*/

namespace libs::ilog_events::events
{
//  forward;
struct RegisterHelper;

/// Базовое сообщение для подсистемы логирования
/// Расширяет интерфейс сообщения для нужд подсистемы логирования
class BaseLogEvent : public ::libs::ievents::TimedEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseLogEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseLogEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (BaseLogEvent)

  explicit BaseLogEvent (const Acessor& = Acessor (0));
  virtual ~BaseLogEvent () = default;

  virtual std::string text (const LogTexts& type) const;

  protected:
  //  ievents::Event overrides
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent)

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  //  ievents::Event overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::BaseLogEvent);
