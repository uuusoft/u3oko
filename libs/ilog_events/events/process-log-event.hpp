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
  \brief  Перечисление различных действий, который можно произвести над списком сессий логирования
  */
enum struct ActionForProcessLog
{
  get_raw_log = 0      //< Получить указанный список сессий логирования. Гарантируется упорядоченность по времени списка логирования, т.е. последний элемент это текущая сессия логирования.
  //get_zip_sessions      = 1 //< Получить сжатый в архив указанный список сессий логирования. Гарантируется упорядоченность по времени списка логирования, т.е. последний элемент это текущая сессия логирования.
};
/**
  \brief
  */
inline std::string
to_str (const ActionForProcessLog& _act)
{
  switch (_act)
    {
    case ActionForProcessLog::get_raw_log:
      return "get raw log";
    default:
      UASSERT_SIGNAL ("unknown ActionForProcessLog");
      break;
    }

  return "???";
}
/**
  \brief  
  */
struct InfoLogSession
{
  typedef std::string data_session_type;      //< Данные сессии.

  InfoLogSession () :
    off_ (0), size_ (0)
  {}


  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (data_);
    ar& BOOST_SERIALIZATION_NVP (off_);
    ar& BOOST_SERIALIZATION_NVP (size_);
    return;
  }

  data_session_type data_;      //< Фрагмент данных сессии.
  int               off_;       //< Смещение фрагмента в байтах.
  int               size_;      //< Маскимальный размер фрагмента в байтах. 0 - не ограниченно.
};
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
  typedef std::string    id_session_type;
  typedef InfoLogSession info_session_type;      //< Информация о сессии. Данные фрагмента, смещение фрагмента, размер данных.
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ProcessLogEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ProcessLogEvent);
  UUU_DISABLE_ACOPY_TYPE (ProcessLogEvent);

  explicit ProcessLogEvent (const Acessor& = Acessor (0), const AppllPartLogInfo& _appl = AppllPartLogInfo ("x7x", __FILE__, __LINE__));

  virtual ~ProcessLogEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
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

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::ProcessLogEvent);
