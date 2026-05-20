#pragma once
/**
\file       process-log-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    uuu_ilog_events
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

  virtual ~ProcessLogEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ilog_events/events/process-log-event";
    return ret;
  }

  const InfoLogSession::id_session_type& get_session () const;
  void                                   set_session (InfoLogSession::id_session_type&& folders);
  const info_session_type&               get_log_info () const;
  void                                   set_log_info (info_session_type&& info);
  LogProcessActions                      get_action () const;
  void                                   set_action (const LogProcessActions& action);
  virtual std::string                    text (const LogTexts& type) const override;

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
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  //  ievents::Event overrides
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::ProcessLogEvent);
