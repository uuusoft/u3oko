#pragma once
/**
\file       info-log-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_log
*/

namespace libs::events_log::events
{
/// Информационное сообщение для сброса его в лог
/// Т.е. это именно сообщение логирования
class InfoLogEvent : public BaseLogEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor;

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (InfoLogEvent)
  U3_ADD_MAKE_SHARED_THIS (InfoLogEvent)
  U3_ADD_DELETE_MOVE_COPY (InfoLogEvent)

  explicit InfoLogEvent (
    const Acessor&          ph   = Acessor (0),
    const AppllPartLogInfo& appl = AppllPartLogInfo (::libs::events_base::props::modules::log::LogLevels::info, "xilex", "xilex"),
    std::string             info = "xxxxxx");

  virtual ~InfoLogEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_log/events/info-log-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_appl_info () const -> const AppllPartLogInfo&;
  auto change_appl_info (const AppllPartLogInfo&, const std::string&) -> void;

  // BaseLogEvent
  virtual std::string text (const LogTexts& type) const override;

  protected:
  AppllPartLogInfo         appl_;   //< Информация о точки логирования
  std::string              info_;   //< Собственно сообщение для логрования
  boost::posix_time::ptime time_;   //< Время генерации сообщения

  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_ADD_SUPER_CLASS (::libs::events_log::events::BaseLogEvent)

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::events_log::events

BOOST_CLASS_EXPORT_KEY (::libs::events_log::events::InfoLogEvent);
