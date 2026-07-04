#pragma once
/**
\file       wrapper-http-event.hpp
\date       21.07.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_user
*/

namespace libs::events_user::events
{
class WrapperUserEvent : public BaseUserEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (WrapperUserEvent)
  U3_ADD_MAKE_SHARED_THIS (WrapperUserEvent)
  U3_ADD_DELETE_MOVE_COPY (WrapperUserEvent)

  explicit WrapperUserEvent (
    const Acessor&                  = Acessor (0),
    ::libs::events::IEvent::ptr msg = ::libs::events::IEvent::ptr ());

  virtual ~WrapperUserEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_user/events/wrapper-user-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_msg () const -> ::libs::events::IEvent::ptr;
  auto set_msg (::libs::events::IEvent::ptr&) -> void;

  protected:
  ::libs::events::IEvent::ptr int_;   //< событие, для которого производится синхронизация

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_user::events::BaseUserEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_user::events

BOOST_CLASS_EXPORT_KEY (::libs::events_user::events::WrapperUserEvent);
