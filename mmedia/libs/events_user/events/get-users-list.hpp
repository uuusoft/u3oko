#pragma once
/**
\file       get-users-list.hpp
\author     Erashov Anton erashov2026@proton.me
\date       23.06.2026
\project    u3_events_user
*/

namespace libs::events_user::events
{
class GetUsersList : public BaseUserEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (GetUsersList)
  U3_ADD_MAKE_SHARED_THIS (GetUsersList)
  U3_ADD_DELETE_MOVE_COPY (GetUsersList)

  using users_list_type = std::vector< syn::user_id_type >;

  explicit GetUsersList (const Acessor& = Acessor (0), const users_list_type& = {});
  virtual ~GetUsersList () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_user/events/get-users-list";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_users_ids () const -> const users_list_type&;

  protected:
  //  events_base::Event overrides
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  users_list_type users_ids_;

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

BOOST_CLASS_EXPORT_KEY (::libs::events_user::events::GetUsersList);
