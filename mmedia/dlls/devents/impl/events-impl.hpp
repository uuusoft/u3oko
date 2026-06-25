#pragma once
/**
\file       events-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       21.07.2017
\project    u3_devents_dlls
*/

namespace dlls::devents::impl
{
struct string_hash {
  using is_transparent = void;   // Enables heterogeneous lookup capability

  std::size_t
  operator() (std::string_view&& sv) const
  {
    return std::hash< std::string_view > {}(sv);
  }

  std::size_t
  operator() (const std::string& str) const
  {
    return std::hash< std::string > {}(str);
  }

  std::size_t
  operator() (const char* ptr) const
  {
    return std::hash< std::string_view > {}(ptr);
  }
};

// EAI-REFACT
template< typename TTVal >
using strings_unordered_map = std::unordered_map< std::string, TTVal, string_hash, std::equal_to<> >;

/// Реализация управлением событиями в системе
class EventsImpl final : public ::libs::events::io::IEvents
{
  public:
  //  ext types
  using id_event_type            = std::string;
  using create_event_func_type   = std::function< syn::IEvent::ptr () >;
  using cast_event_func_type     = std::function< const void*(syn::IEvent::craw_ptr) >;
  using str2gen_events_type      = strings_unordered_map< create_event_func_type >;
  using str2cast_events_type     = strings_unordered_map< cast_event_func_type >;
  using str2_counter_events_type = strings_unordered_map< std::uint64_t >;
  using sync_type                = std::mutex;
  using lock_type                = std::scoped_lock< sync_type >;

  EventsImpl ();
  virtual ~EventsImpl () = default;

  EventsImpl (const EventsImpl&)            = delete;
  EventsImpl& operator= (const EventsImpl&) = delete;

  //  IEvents overrides
  virtual auto get (const hid_type& id) -> syn::IEvent::ptr override;
  virtual auto clone (const syn::IEvent::craw_ptr src, const ::libs::events::Deeps& type) -> syn::IEvent::ptr override;
  virtual auto dcast (syn::IEvent::craw_ptr src, const hid_type& id) -> const void* override;
  virtual auto event2xml (syn::IEvent::ptr& src, std::string& xml) -> bool override;
  virtual auto xml2event (const std::string& xml, syn::IEvent::ptr& dst) -> bool override;
  virtual auto event2bin (syn::IEvent::ptr& src, std::ostream& bin) -> bool override;
  virtual auto bin2event (std::istream& bin, syn::IEvent::ptr& dst) -> bool override;

  private:
  auto make_event_funcs () -> void;
  auto dbg_state_dump () -> void;

  template< typename TTEvent >
  void
  add_event_generator ()
  {
    gen_func_events_[id_event_type { TTEvent::gen_get_mid () }] = [] () {
      return std::make_shared< TTEvent > ();
    };
  }

  template< typename TTEvent >
  void
  add_event_cast ()
  {
    U3_XLOG_DBG ("add create func event to gloabl table" + STOLOG (TTEvent::gen_get_mid ()));
    cast_func_events_[id_event_type { TTEvent::gen_get_mid () }] = [] (::libs::events::IEvent::craw_ptr src) -> const void* {
      auto* res = dynamic_cast< typename TTEvent::craw_ptr > (src);
      U3_XLOG_DEV ("cast to::---->" + STOLOG (TTEvent::gen_get_mid ()) + PTR_TOLOG (src) + PTR_TOLOG (res));
      return res;
    };
  }

  template< typename TTEvent >
  void
  add_event ()
  {
    add_event_generator< TTEvent > ();
    add_event_cast< TTEvent > ();
  }

  str2gen_events_type      gen_func_events_;         //< Функции для создания событий по их идентификаторам
  str2cast_events_type     cast_func_events_;        //< Функции преобразования событий
  sync_type                mtx_;                     //< Синхронизирущий примитив
  str2_counter_events_type counter_create_events_;   //< debug
  str2_counter_events_type counter_clone_events_;    //< debug
};
}   // namespace dlls::devents::impl
