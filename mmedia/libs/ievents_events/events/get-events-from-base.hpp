#pragma once
/**
\file       get-events-from-base.hpp
\author     Erashov Anton erashov2026@proton.me
\date       09.09.2018
\project    u3_ievents_lib
*/

namespace libs::ievents_events::events
{
class GetEventsFromBase : public BaseEventsEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  static constexpr std::uint32_t max_events_cout_per_call = 1000;

  // ext types
  using request_params_type  = ::boost::json::value;
  using database_events_type = std::vector< IEvent::ptr >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (GetEventsFromBase)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GetEventsFromBase)
  U3_HELPER_DISABLE_ACOPY_TYPE (GetEventsFromBase)

  GetEventsFromBase (const Acessor& = Acessor (0));
  virtual ~GetEventsFromBase () = default;

  constexpr static auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents_events/events/get-events-from-base";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  auto sync_event_props (
    const time_period_type&,
    const id_graphs_storage_type&,
    const hids_storage_type&,
    const database_events_type&,
    const request_params_type&) -> void;
#endif

  auto sync_event_props (const request_params_type&, const database_events_type&) -> void;
  auto set_request (request_params_type&) -> void;
  auto get_request () const -> const request_params_type&;
  auto set_events (database_events_type& events) -> void;
  auto get_events () const -> const database_events_type&;

  private:
  //  internal typess
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (BaseEventsEvent)

  request_params_type  request_params_;    //<
  database_events_type database_events_;   //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ievents_events::events::GetEventsFromBase);
