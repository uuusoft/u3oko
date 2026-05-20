#pragma once
/**
\file       info-log-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    uuu_ilog_events
*/

namespace libs::ilog_events::events
{
/// Информационное сообщение для сброса его в лог. Т.е. это именно сообщение логирования
class InfoLogEvent : public BaseLogEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (InfoLogEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (InfoLogEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (InfoLogEvent)

  explicit InfoLogEvent (
    const Acessor&          ph   = Acessor (0),
    const AppllPartLogInfo& appl = AppllPartLogInfo (::libs::ievents::props::modules::log::LogLevels::info, "xilex", "xilex"),
    const std::string&      info = "xxxxxx");

  virtual ~InfoLogEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string ret = "libs/ilog_events/events/info-log-event";
    return ret;
  }

  const AppllPartLogInfo& get_appl_info () const;
  void                    change_appl_info (const AppllPartLogInfo& appl, const std::string& info);
  virtual std::string     text (const LogTexts& type) const override;

  protected:
  AppllPartLogInfo         appl_;   //< Информация о точки логирования
  std::string              info_;   //< Собственно сообщение для логрования
  boost::posix_time::ptime time_;   //< Время генерации сообщения

  virtual void copy_int (const IEvent::craw_ptr src) override;

  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilog_events::events::BaseLogEvent)

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
};
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::InfoLogEvent);
