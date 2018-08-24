#pragma once
/**
\file       change-state-sub-sys-log-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief      empty brief
*/

namespace libs { namespace ilog_events { namespace events {
/**
  \brief  Информационное сообщение о изменении состояния работы подсистемы (любой).
  */
class ChangStateProcessTypeSubSysLogEvent : public InfoLogEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ChangStateProcessTypeSubSysLogEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ChangStateProcessTypeSubSysLogEvent);
  UUU_DISABLE_ACOPY_TYPE (ChangStateProcessTypeSubSysLogEvent);

  explicit ChangStateProcessTypeSubSysLogEvent (const Acessor& = Acessor (0));

  ChangStateProcessTypeSubSysLogEvent (const Acessor&, const AppllPartLogInfo& _appl, bool _start);

  virtual ~ChangStateProcessTypeSubSysLogEvent ()
  {}

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ilog_events/events/change-state-process-type-sub-sys-log-event";
    return _ret;
  }

  bool is_start () const;

  void set_start (bool _val);

  //  InfoLogEvent overrides
  virtual std::string text (const TypeLogText& _type) const override;


  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (InfoLogEvent);

  bool start_;      //< ???

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::ChangStateProcessTypeSubSysLogEvent);
