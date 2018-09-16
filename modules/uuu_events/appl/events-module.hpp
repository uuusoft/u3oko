#pragma once
/**
\file       events-module.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace modules { namespace uuu_events { namespace appl {
/**
\brief  Реализация модуля для хранения событий системы.
*/
class EventsModule final : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  friend void error_callback (void* _pArg, int _code, const char* _msg);

  EventsModule ();

  virtual ~EventsModule ();


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule);
  //  BaseModule overrides
  virtual void init_int (const InitApplication& _info) override;
  virtual void init_links_int (const InitApplication& _info) override;
  virtual void init_proxys_int () override;
  virtual bool deinit_int () override;
  virtual void update_catch_functs_int () override;
  //  LeafModule overrides
  virtual recv_links_type get_recv_link () override;
  virtual bool            catch_event (IEvent::ptr _evnt) override;
  virtual bool            is_now_sleep_thread (bool _now_recv_evnt) override;

  void check_process ();

  void error_callback (const std::string& _error_text);

  void process_change_state_process (ChangStateProcessTypeEvent::raw_ptr _props);
  
  void process_add_event2base (AddEvent2Base::raw_ptr _props);

  sqlite3* pbase_;      //< База данных с событиями.
};

}}}      // namespace modules::uuu_events::appl
