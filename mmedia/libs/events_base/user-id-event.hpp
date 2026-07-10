#pragma once
/**
\file       user-id-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2026
\project    u3_events_base_lib
*/

namespace libs::events_base
{
class UserIdEvent : virtual public events_base::OpsStatusEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (UserIdEvent)
  U3_ADD_MAKE_SHARED_THIS (UserIdEvent)
  U3_ADD_DELETE_MOVE_COPY (UserIdEvent)

  using user_id_type         = ::libs::utility::utils::cuuid;
  using user_session_id_type = ::libs::utility::utils::cuuid;

  explicit UserIdEvent (const Acessor& = Acessor (0), const user_id_type& = {}, const user_session_id_type& = {});
  virtual ~UserIdEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/user-id-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto set_user_id (user_id_type) -> void;
  auto get_user_id () const -> const user_id_type&;
  auto set_user_session_id (user_session_id_type) -> void;
  auto get_user_session_id () const -> const user_session_id_type&;

  protected:
  user_id_type         user_id_;           //<
  user_session_id_type user_session_id_;   //<

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
  // virtual auto load_json_int (const ::boost::json::object&) -> void override;
  // virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_base::OpsStatusEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events_base

BOOST_CLASS_EXPORT_KEY (::libs::events_base::UserIdEvent);
