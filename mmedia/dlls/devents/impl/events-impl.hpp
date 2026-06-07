#pragma once
/**
\file       events-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       21.07.2017
\project    u3_devents_dlls
*/

namespace dlls::devents::impl
{
/// Реализация управлением событиями в системе
class EventsImpl final : public ::libs::events::io::IEvents
{
  public:
  //  ext types
  using create_event_func_type   = std::function< syn::IEvent::ptr () >;
  using str2gen_events_type      = std::unordered_map< hid_type, create_event_func_type >;
  using cast_event_func_type     = std::function< syn::IEvent::craw_ptr (syn::IEvent::craw_ptr) >;
  using str2cast_events_type     = std::unordered_map< hid_type, cast_event_func_type >;
  using str2_counter_events_type = std::unordered_map< hid_type, std::uint64_t >;
  using sync_type                = std::mutex;
  using lock_type                = std::scoped_lock< sync_type >;

  EventsImpl ();
  virtual ~EventsImpl () = default;

  //  IEvents overrides
  virtual syn::IEvent::ptr get (const hid_type& id) override;
  virtual syn::IEvent::ptr clone (const syn::IEvent::craw_ptr src, const ::libs::events::Deeps& type) override;
  virtual void*            dcast (syn::IEvent::craw_ptr src, const hid_type& id) override;
  virtual bool             event2xml (syn::IEvent::ptr& src, std::string& xml) override;
  virtual bool             xml2event (const std::string& xml, syn::IEvent::ptr& dst) override;
  virtual bool             event2bin (syn::IEvent::ptr& src, std::ostream& bin) override;
  virtual bool             bin2event (std::istream& bin, syn::IEvent::ptr& dst) override;

  private:
  void construct_func_event ();

  template< typename TTEvent >
  void
  add_event_generator ()
  {
    gen_func_events_[TTEvent::gen_get_mid ()] = [] () { return std::make_shared< TTEvent > (); };
  }

  template< typename TTEvent >
  void
  add_event_cast ()
  {
    cast_func_events_[TTEvent::gen_get_mid ()] = [] (::libs::events::IEvent::craw_ptr src) -> ::libs::events::IEvent::craw_ptr {
      auto res = dynamic_cast< typename TTEvent::craw_ptr > (src);
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
