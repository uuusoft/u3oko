#pragma once
/**
\file       ops-status-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base
{
class OpsStatusEvent : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (OpsStatusEvent)
  U3_ADD_MAKE_SHARED_THIS (OpsStatusEvent)
  U3_ADD_DELETE_MOVE_COPY (OpsStatusEvent)

  explicit OpsStatusEvent (const Acessor& = Acessor (0));
  virtual ~OpsStatusEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/ops-status-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_ops_status () const -> OpsStatus;
  auto set_ops_status (const OpsStatus& val) -> void;
  auto get_ops_info () const -> const std::string&;
  auto set_ops_info (const std::string& val) -> void;

  protected:
  OpsStatus   ops_status_    = OpsStatus::unset;   //<
  std::string ops_json_info_ = "{}";               //<

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events_base

BOOST_CLASS_EXPORT_KEY (::libs::events_base::OpsStatusEvent);
BOOST_CLASS_TRACKING (::libs::events_base::OpsStatusEvent, boost::serialization::track_always);
