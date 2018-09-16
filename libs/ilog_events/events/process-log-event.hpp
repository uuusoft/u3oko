#pragma once
/**
\file       process-log-event.hpp
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
class ProcessLogEvent : public BaseLogEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  //  ext types
  using id_session_type   = std::string;
  using info_session_type = InfoLogSession;      //< Информация о сессии. Данные фрагмента, смещение фрагмента, размер данных.
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ProcessLogEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ProcessLogEvent);
  UUU_DISABLE_ACOPY_TYPE (ProcessLogEvent);

  explicit ProcessLogEvent (const Acessor& = Acessor (0), const AppllPartLogInfo& _appl = AppllPartLogInfo ("x7x", __FILE__, __LINE__));

  virtual ~ProcessLogEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ilog_events/events/process-log-event";
    return _ret;
  }

  const id_session_type& get_session () const;

  void set_session (id_session_type&& _folders);

  const info_session_type& get_log_info () const;

  void set_log_info (info_session_type&& _info);

  ActionForProcessLog get_action () const;

  void set_action (const ActionForProcessLog& _action);

  virtual std::string text (const TypeLogText& _type) const override;


  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseLogEvent);

  id_session_type     session_;      //< Каталог сессии логирования.
  ActionForProcessLog action_;       //< Тип полученения данных из списка файлов сессии.
  InfoLogSession      info_;         //< Данные файлов сессии логирования.

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
  //  ievents::Event overrides
  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::ProcessLogEvent);
