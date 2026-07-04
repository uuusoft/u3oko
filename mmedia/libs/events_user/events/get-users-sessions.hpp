#pragma once
/**
\file       get-users-sessions.hpp
\author     Erashov Anton erashov2026@proton.me
\date       24.07.2018
\project    u3_events_user
*/

namespace libs::events_user::events
{
#if 0  
struct RuntimeStreamInfo {
  RuntimeStreamInfo () = default;

  void
  reset ()
  {
    stream_id_         = consts::empty_stream_id;
    count_write_bytes_ = 0;
    count_read_bytes_  = 0;
    count_errors_      = 0;
  }

  stream_id_type stream_id_         = consts::empty_stream_id;   //<
  std::uint64_t  count_write_bytes_ = 0;                         //<
  std::uint64_t  count_read_bytes_  = 0;                         //<
  std::uint64_t  count_errors_      = 0;                         //<

  private:
  friend class boost::serialization::access;

  // REFACT
  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */)
  {
    arh& BOOST_SERIALIZATION_NVP (stream_id_);
    arh& BOOST_SERIALIZATION_NVP (count_write_bytes_);
    arh& BOOST_SERIALIZATION_NVP (count_read_bytes_);
    arh& BOOST_SERIALIZATION_NVP (count_errors_);
  }
};
#endif

class GetUsersSessions : public BaseUserEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  using session_info_type   = std::string;
  using sessions_users_type = std::vector< session_info_type >;

  U3_ADD_POINTERS_TO_SELF (GetUsersSessions)
  U3_ADD_MAKE_SHARED_THIS (GetUsersSessions)
  U3_ADD_DELETE_MOVE_COPY (GetUsersSessions)

  explicit GetUsersSessions (const Acessor& = Acessor (0), const syn::user_id_type& = {});
  virtual ~GetUsersSessions () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_user/events/get-users-sessions";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto set_user_id (user_id_type) -> void;
  auto get_user_id () const -> const user_id_type&;
  auto get_sessions () -> const sessions_users_type&;
  auto set_sessions (const sessions_users_type&) -> void;

  protected:
  //  events_base::Event overrides
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  syn::user_id_type   user_id_;    //<
  sessions_users_type sessions_;   //<

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_user::events::BaseUserEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::events_user::events

BOOST_CLASS_EXPORT_KEY (::libs::events_user::events::GetUsersSessions);
