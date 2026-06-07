#pragma once
/**
\file       get-events-from-base.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  // ext types
  using events_res_type        = std::vector< IEvent::ptr >;
  using hids_storage_type      = std::vector< IEvent::hid_type >;
  using time_point_type        = ::libs::helpers::time::TimePoint;
  using time_period_type       = std::pair< time_point_type, time_point_type >;
  using id_graphs_storage_type = GetDataGraphsFromEventBase::id_graphs_storage_type;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (GetEventsFromBase)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GetEventsFromBase)
  U3_HELPER_DISABLE_ACOPY_TYPE (GetEventsFromBase)

  GetEventsFromBase (const Acessor& = Acessor (0));
  virtual ~GetEventsFromBase () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents_events/events/get-events-from-base";
    return ret;
  }

  void sync_event_props (
    const time_period_type&       time_period,
    const id_graphs_storage_type& data_graph_ids,
    const hids_storage_type&      event_types,
    const events_res_type&        events_from_database,
    const std::string&            sql_request);

  void                          set_data_graphs (id_graphs_storage_type& events);
  const id_graphs_storage_type& get_data_graphs () const;
  void                          set_events (events_res_type& events);
  const events_res_type&        get_events () const;
  void                          set_types (hids_storage_type& types);
  const hids_storage_type&      get_types () const;
  void                          set_request (std::string&);
  const std::string&            get_request () const;

  private:
  //  internal typess
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (BaseEventsEvent)

  time_period_type       time_period_;            //<
  id_graphs_storage_type data_graph_ids_;         //<
  hids_storage_type      event_types_;            //<
  events_res_type        events_from_database_;   //<
  std::string            sql_request_;            //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ievents_events::events::GetEventsFromBase);
