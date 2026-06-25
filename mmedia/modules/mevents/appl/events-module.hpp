#pragma once
/**
\file       events-module.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mevents
*/

namespace modules::mevents::appl
{
struct ControlSizeDataBase {
  static constexpr std::uint64_t max_count_msg_without_check = 1000;

  ControlSizeDataBase ()  = default;
  ~ControlSizeDataBase () = default;

  ControlSizeDataBase& operator= (const ControlSizeDataBase&) = delete;
  ControlSizeDataBase& operator= (ControlSizeDataBase&&)      = delete;

  auto
  compression_requared (SQLite::Database* database) -> bool
  {
    U3_CHECK (database, "empty database");
    if (++msg_counter_ < max_count_msg_without_check)
    {
      return false;
    }

    // database->

    msg_counter_ = 0;
    return true;
  }

  auto
  reset () -> void
  {
    msg_counter_ = 0;
  }

  std::uint64_t msg_counter_ = 0;
};

/// Реализация модуля для хранения событий системы
class EventsModule final : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  EventsModule ();
  virtual ~EventsModule ();

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule)

  friend auto free_error_callback (void*, int, const char*) -> void;

  //  IApplication overrides
  virtual auto init_appl_data_int () -> void override;

  //  BaseModule overrides
  virtual auto appl_init_int (const ::libs::link::appl::InitApplication& info) -> void override;
  virtual auto init_links_int (const ::libs::link::appl::InitApplication& info) -> void override;
  virtual auto init_proxys_int () -> void override;
  virtual auto appl_deinit_int () -> bool override;
  virtual auto update_catch_funcs_int () -> void override;
  virtual auto get_recv_link_int () -> recv_links_type override;
  virtual auto init_done_int () -> void override;

  //  LeafModule overrides
  virtual auto catch_event_int (syn::IEvent::ptr& evnt) -> bool override;
  virtual auto is_now_thread_to_sleep_int (bool now_recv_evnt) -> bool override;

  auto check_process () -> void;
  auto error_callback (const std::string& error_text) -> void;
  auto prepare_base () -> void;
  auto shutdown_base () -> void;
  auto process_change_state_process (syn::IEvent::ptr&, syn::ChangeStateProcessEvent::raw_ptr) -> void;
  auto process_add_event2base (syn::IEvent::ptr&, syn::AddEvent2Base::raw_ptr) -> void;
  auto process_get_data_graphs (syn::IEvent::ptr&, syn::GetDataGraphsFromEventBase::raw_ptr) -> void;
  auto process_update_listener (syn::IEvent::ptr&, syn::UpdateListener::raw_ptr) -> void;
  auto process_get_events_from_base (syn::IEvent::ptr&, syn::GetEventsFromBase::raw_ptr) -> void;

  std::unique_ptr< SQLite::Database > base_;              //< База данных с событиями
  ControlSizeDataBase                 size_controller_;   //<
};
}   // namespace modules::mevents::appl
