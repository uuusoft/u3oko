#pragma once
/**
\file       change-state-sub-sys-log-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_log
*/

namespace libs::events_log::events
{
/// Информационное сообщение о изменении состояния работы подсистемы (любой)
class ChangeStateSubSysLogEvent final : public InfoLogEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor;

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (ChangeStateSubSysLogEvent)
  U3_ADD_MAKE_SHARED_THIS (ChangeStateSubSysLogEvent)
  U3_ADD_DELETE_MOVE_COPY (ChangeStateSubSysLogEvent)

  explicit ChangeStateSubSysLogEvent (const Acessor& = Acessor (0));
  ChangeStateSubSysLogEvent (const Acessor&, const AppllPartLogInfo& appl, bool start);
  virtual ~ChangeStateSubSysLogEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_log/events/change-state-process-type-sub-sys-log-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  bool is_start () const;
  void set_start (bool val);

  // BaseLogEvent overrides
  virtual std::string text (const LogTexts& type) const override;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_ADD_SUPER_CLASS (::libs::events_log::events::InfoLogEvent)

  bool start_ = false;   //<

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_log::events

BOOST_CLASS_EXPORT_KEY (::libs::events_log::events::ChangeStateSubSysLogEvent);
