#pragma once
/**
\file       process-log-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ilog_events
*/

namespace libs::ilog_events::events
{
/// Событие с списком сессий логирования и действием над ним
class ProcessLogEvent final : public BaseLogEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  //  ext types
  using info_session_type = InfoLogSessionFragment;   //< информация о сессии Данные фрагмента, смещение фрагмента, размер данных

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ProcessLogEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ProcessLogEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ProcessLogEvent)

  explicit ProcessLogEvent (
    const Acessor&               = Acessor (0),
    const AppllPartLogInfo& appl = AppllPartLogInfo (::libs::ievents::props::modules::log::LogLevels::info, "xplex", "xplex"));

  virtual ~ProcessLogEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ilog_events/events/process-log-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_session () const -> const InfoLogSession::id_session_type&;
  auto set_session (InfoLogSession::id_session_type&& folders) -> void;
  auto get_log_info () const -> const info_session_type&;
  auto set_log_info (info_session_type&& info) -> void;
  auto get_action () const -> LogProcessActions;
  auto set_action (const LogProcessActions& action) -> void;

  // BaseLogEvent
  virtual std::string text (const LogTexts& type) const override;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilog_events::events::BaseLogEvent)

  InfoLogSession::id_session_type session_;   //< идентификатор сессии логирования (фактически каталог)
  LogProcessActions               action_;    //< тип полученения данных из списка файлов сессии
  InfoLogSessionFragment          info_;      //< данные файлов сессии логирования

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  //  ievents::Event overrides
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::ProcessLogEvent);
