#pragma once
/**
\file       info-log-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief      empty brief
*/

namespace libs { namespace ilog_events { namespace events {
/**
\brief  Информационное сообщение для сброса его в лог. Т.е. это именно сообщение логирования.
*/
class InfoLogEvent : public BaseLogEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (InfoLogEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (InfoLogEvent);
  UUU_DISABLE_ACOPY_TYPE (InfoLogEvent);

  explicit InfoLogEvent (
    const Acessor&                = Acessor (0),
    const AppllPartLogInfo& _appl = AppllPartLogInfo ("xxx", __FILE__, __LINE__),
    const std::string&      _info = "xxx");

  virtual ~InfoLogEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ilog_events/events/info-log-event";
    return _ret;
  }

  void update_info (const AppllPartLogInfo& _appl, const std::string& _info);

  virtual std::string text (const TypeLogText& _type) const override;


  protected:
  AppllPartLogInfo         appl_;      //< Информация о приложении.
  std::string              info_;      //< Собственно сообщение.
  boost::posix_time::ptime time_;      //< Время генерации сообщения.

  virtual void copy_int (const IEvent::craw_ptr _src) override;

  struct Acessor
  {
    explicit Acessor (int){};
  };


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseLogEvent);

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
};

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::InfoLogEvent);
