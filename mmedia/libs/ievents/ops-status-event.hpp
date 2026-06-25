#pragma once
/**
\file       ops-status-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents
{
class OpsStatusEvent : virtual public ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (OpsStatusEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (OpsStatusEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (OpsStatusEvent)

  explicit OpsStatusEvent (const Acessor& = Acessor (0));
  virtual ~OpsStatusEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/ops-status-event";
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

  //  ievents::Event overrides
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::ievents

BOOST_CLASS_EXPORT_KEY (::libs::ievents::OpsStatusEvent);
BOOST_CLASS_TRACKING (::libs::ievents::OpsStatusEvent, boost::serialization::track_always);
