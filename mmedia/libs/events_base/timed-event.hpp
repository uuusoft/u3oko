#pragma once
/**
\file       timed-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base
{
/// Базовый класс всех событий системы с временной меткой
class TimedEvent : virtual public events_base::UserIdEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (TimedEvent)
  U3_ADD_MAKE_SHARED_THIS (TimedEvent)
  U3_ADD_DELETE_MOVE_COPY (TimedEvent)

  using time_type = boost::posix_time::ptime;

  explicit TimedEvent (const Acessor& = Acessor (0));
  virtual ~TimedEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/timed-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_time () const -> const time_type&;

  protected:
  time_type time_;   //<

  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_base::UserIdEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::events_base

BOOST_CLASS_EXPORT_KEY (::libs::events_base::TimedEvent);
