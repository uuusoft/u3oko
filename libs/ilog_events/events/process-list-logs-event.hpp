#pragma once
/**
\file       process-list-logs-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief    
*/

namespace libs { namespace ilog_events { namespace events {
/**
\brief  Событие с списком сессий логирования и действием над ним.
*/
class ProcessListLogsEvent : public BaseLogEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  //  ext types
  using id_session_type   = std::string;
  using list_folders_type = std::vector<id_session_type>;      //< Список сессий логирования.
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ProcessListLogsEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ProcessListLogsEvent);
  UUU_DISABLE_ACOPY_TYPE (ProcessListLogsEvent);

  explicit ProcessListLogsEvent (const Acessor& = Acessor (0), const AppllPartLogInfo& _appl = AppllPartLogInfo ("x6x", __FILE__, __LINE__));

  virtual ~ProcessListLogsEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ilog_events/events/process-list-logs-event";
    return _ret;
  }

  const list_folders_type& get_sessions () const;

  void set_sessions (list_folders_type&& _folders);

  ActionForListLogs get_action () const;

  void set_action (const ActionForListLogs& _action);

  virtual std::string text (const TypeLogText& _type) const override;


  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseLogEvent);

  ActionForListLogs action_;       //< Тип действия над списком сессий
  list_folders_type folders_;      //< Список директорий с логирванием. Т.е. фактически списк сессий логирования.

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
  //  ievents::Event overrides
  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::ProcessListLogsEvent);
