#pragma once
/**
\file       change-state-sub-sys-log-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilog_events
*/

namespace libs::ilog_events::events
{
/// Информационное сообщение о изменении состояния работы подсистемы (любой)
class ChangDShowRunsSubSysLogEvent final : public InfoLogEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ChangDShowRunsSubSysLogEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ChangDShowRunsSubSysLogEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ChangDShowRunsSubSysLogEvent)

  explicit ChangDShowRunsSubSysLogEvent (const Acessor& = Acessor (0));

  ChangDShowRunsSubSysLogEvent (const Acessor&, const AppllPartLogInfo& appl, bool start);

  virtual ~ChangDShowRunsSubSysLogEvent ()
  {
  }

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ilog_events/events/change-state-process-type-sub-sys-log-event";
    return ret;
  }

  bool is_start () const;
  void set_start (bool val);

  //  InfoLogEvent overrides
  virtual std::string text (const LogTexts& type) const override;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilog_events::events::InfoLogEvent)

  bool start_;   //<

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent);
