#pragma once
/**
\file       wrapper-http-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_http
*/

namespace libs::events_http::events
{
/// Класс событие для обертки другого события с целью указания модуля-назначения в виде http сервера
class WrapperHttpEvent : public BaseHttpEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (WrapperHttpEvent)
  U3_ADD_MAKE_SHARED_THIS (WrapperHttpEvent)
  U3_ADD_DELETE_MOVE_COPY (WrapperHttpEvent)

  explicit WrapperHttpEvent (
    const Acessor&                  = Acessor (0),
    ::libs::events::IEvent::ptr msg = ::libs::events::IEvent::ptr ());

  virtual ~WrapperHttpEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_http/events/wrapper-http-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_msg () const -> ::libs::events::IEvent::ptr;
  auto set_msg (::libs::events::IEvent::ptr& msg) -> void;

  protected:
  ::libs::events::IEvent::ptr int_;   //< событие, для которого производится синхронизация

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& prop ) override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_http::events

BOOST_CLASS_EXPORT_KEY (::libs::events_http::events::WrapperHttpEvent);
