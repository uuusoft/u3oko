#pragma once
/**
\file       base-log-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_log
*/

namespace libs::events_log::events
{
/// Базовое сообщение для подсистемы логирования
/// Расширяет интерфейс сообщения для нужд подсистемы логирования
class BaseLogEvent : public ::libs::events_base::TimedEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor;

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (BaseLogEvent)
  U3_ADD_MAKE_SHARED_THIS (BaseLogEvent)
  U3_ADD_DELETE_MOVE_COPY (BaseLogEvent)

  explicit BaseLogEvent (const Acessor& = Acessor (0));
  virtual ~BaseLogEvent () = default;

  virtual std::string text (const LogTexts& type) const;

  protected:
  //  events_base::Event overrides
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::TimedEvent)

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::events_log::events

BOOST_CLASS_EXPORT_KEY (::libs::events_log::events::BaseLogEvent);
