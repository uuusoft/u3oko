#pragma once
/**
\file       base-events-msg.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_msg::events
{
/// Базовый класс для событий подсистемы "события"
class BaseEventsMsg : public ::libs::events_base::TimedEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (BaseEventsMsg)
  U3_ADD_MAKE_SHARED_THIS (BaseEventsMsg)
  U3_ADD_DELETE_MOVE_COPY (BaseEventsMsg)

  BaseEventsMsg (const Acessor& = Acessor (0));
  virtual ~BaseEventsMsg () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_msg/events/base-events-msg";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  protected:
  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events_msg::events

BOOST_CLASS_EXPORT_KEY (::libs::events_msg::events::BaseEventsMsg);
