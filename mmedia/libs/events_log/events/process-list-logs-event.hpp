#pragma once
/**
\file       process-list-logs-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_log
*/

namespace libs::events_log::events
{
/// Событие с списком сессий логирования и действием над ним
class ProcessListLogsEvent final : public BaseLogEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor;

  public:
  //  ext types
  using list_folders_type = std::vector< InfoLogSession >;   //< тип списка сессий логирования

  U3_ADD_POINTERS_TO_SELF (ProcessListLogsEvent)
  U3_ADD_MAKE_SHARED_THIS (ProcessListLogsEvent)
  U3_ADD_DELETE_MOVE_COPY (ProcessListLogsEvent)

  explicit ProcessListLogsEvent (
    const Acessor&               = Acessor (0),
    const AppllPartLogInfo& appl = AppllPartLogInfo (::libs::events_base::props::modules::log::LogLevels::info, "xpllex", "xpllex"));

  virtual ~ProcessListLogsEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_log/events/process-list-logs-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_sessions () const -> const list_folders_type&;
  auto set_sessions (list_folders_type&& folders) -> void;
  auto get_action () const -> LogActions;
  auto set_action (const LogActions& action) -> void;

  // BaseLogEvent
  virtual std::string text (const LogTexts& type) const override;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_ADD_SUPER_CLASS (::libs::events_log::events::BaseLogEvent)

  LogActions        action_;    //< Тип действия над списком сессий
  list_folders_type folders_;   //< Список директорий с логированием. Т.е. фактически это список сессий логирования

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_log::events

BOOST_CLASS_EXPORT_KEY (::libs::events_log::events::ProcessListLogsEvent);
