#pragma once
/**
\file       events-module.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_module_events
*/

namespace modules::u3_events::appl
{
/// Реализация модуля для хранения событий системы
class EventsModule final : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  EventsModule ();
  virtual ~EventsModule ();

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule)

  friend void free_error_callback (void* pArg, int code, const char* msg);

  //  IApplication overrides
  virtual void init_appl_data_int () override;

  //  BaseModule overrides
  virtual void appl_init_int (const ::libs::link::appl::InitApplication& info) override;
  virtual void init_links_int (const ::libs::link::appl::InitApplication& info) override;
  virtual void init_proxys_int () override;
  virtual bool appl_deinit_int () override;
  virtual void update_catch_funcs_int () override;

  //  LeafModule overrides
  virtual recv_links_type get_recv_link () override;
  virtual bool            catch_event (syn::IEvent::ptr& evnt) override;
  virtual bool            is_now_thread_to_sleep (bool now_recv_evnt) override;

  void check_process ();
  void error_callback (const std::string& error_text);
  void prepare_base ();
  void shutdown_base ();
  void process_change_state_process (syn::IEvent::ptr& msg, syn::ChangeStateProcessEvent::raw_ptr props);
  void process_add_event2base (syn::IEvent::ptr& msg, syn::AddEvent2Base::raw_ptr props);
  void process_get_data_graphs (syn::IEvent::ptr& msg, syn::GetDataGraphsFromEventBase::raw_ptr props);
  void process_update_listener (syn::IEvent::ptr& msg, syn::UpdateListener::raw_ptr props);

  sqlite3* pbase_ = nullptr;   //< База данных с событиями
};
}   // namespace modules::u3_events::appl
