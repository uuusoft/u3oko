#pragma once
/**
\file       except-log-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilog_events
*/

namespace libs::ilog_events::events
{
class ExceptLogEvent final : public InfoLogEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ExceptLogEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ExceptLogEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ExceptLogEvent)

  explicit ExceptLogEvent (
    const Acessor&          ph   = Acessor (0),
    const AppllPartLogInfo& appl = AppllPartLogInfo (::libs::ievents::props::modules::log::LogLevels::info, "xelex", "xelex"),
    const std::string&      info = "???");

  virtual ~ExceptLogEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ilog_events/events/except-log-event";
    return ret;
  }

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilog_events::events::InfoLogEvent)


  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::ExceptLogEvent);
