#pragma once
/**
\file       process-list-logs-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    uuu_ilog_events
*/

namespace libs::ilog_events::events
{
/// Событие с списком сессий логирования и действием над ним
class ProcessListLogsEvent final : public BaseLogEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  //  ext types
  using list_folders_type = std::vector< InfoLogSession >;   //< тип списка сессий логирования

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ProcessListLogsEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ProcessListLogsEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ProcessListLogsEvent)

  explicit ProcessListLogsEvent (
    const Acessor&               = Acessor (0),
    const AppllPartLogInfo& appl = AppllPartLogInfo (::libs::ievents::props::modules::log::LogLevels::info, "xpllex", "xpllex"));

  virtual ~ProcessListLogsEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ilog_events/events/process-list-logs-event";
    return ret;
  }

  const list_folders_type& get_sessions () const;
  void                     set_sessions (list_folders_type&& folders);
  LogActions               get_action () const;
  void                     set_action (const LogActions& action);
  virtual std::string      text (const LogTexts& type) const override;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilog_events::events::BaseLogEvent)

  LogActions        action_;    //< Тип действия над списком сессий
  list_folders_type folders_;   //< Список директорий с логированием. Т.е. фактически это список сессий логирования

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  //  ievents::Event overrides
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::ProcessListLogsEvent);
