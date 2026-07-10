#pragma once
/**
\file       base-http-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_http
*/

namespace libs::events_http::events
{
/// Базовый класс для событий подсистемы "http сервер"
class BaseHttpEvent : public ::libs::events_base::TimedEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (BaseHttpEvent)
  U3_ADD_MAKE_SHARED_THIS (BaseHttpEvent)
  U3_ADD_DELETE_MOVE_COPY (BaseHttpEvent)

  BaseHttpEvent (const Acessor& = Acessor (0));
  virtual ~BaseHttpEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_http/events/base-http-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  protected:
  //  BaseHttpEvent overrides
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& prop ) override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::events_http::events

BOOST_CLASS_EXPORT_KEY (::libs::events_http::events::BaseHttpEvent);
