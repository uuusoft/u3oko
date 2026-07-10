#pragma once
/**
\file       wrapper-events-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_msg::events
{
/// Класс событие для обертки другого события с целью указания модуля-назначения в виде сервера событий
class WrapperEventsEvent : public BaseEventsMsg
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (WrapperEventsEvent)
  U3_ADD_MAKE_SHARED_THIS (WrapperEventsEvent)
  U3_ADD_DELETE_MOVE_COPY (WrapperEventsEvent)

  explicit WrapperEventsEvent (const Acessor& = Acessor (0), ::libs::events::IEvent::ptr msg = ::libs::events::IEvent::ptr ());
  virtual ~WrapperEventsEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_msg/events/wrapper-events-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_msg () const -> ::libs::events::IEvent::ptr;
  auto set_msg (::libs::events::IEvent::ptr&) -> void;

  protected:
  ::libs::events::IEvent::ptr int_;   //< Событие, которое требуется передать в подсистему

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_msg::events

BOOST_CLASS_EXPORT_KEY (::libs::events_msg::events::WrapperEventsEvent);
