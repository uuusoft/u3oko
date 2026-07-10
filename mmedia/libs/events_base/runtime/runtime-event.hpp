#pragma once
/**
\file       runtime-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime
{
/// Базовый класс всех событий системы с временной меткой
class RuntimeEvent : virtual public TimedEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (std::int32_t) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (RuntimeEvent)
  U3_ADD_MAKE_SHARED_THIS (RuntimeEvent)
  U3_ADD_DELETE_MOVE_COPY (RuntimeEvent)

  explicit RuntimeEvent (const Acessor& = Acessor (0));
  virtual ~RuntimeEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/runtime/runtime-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  protected:
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_base::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::events_base::runtime

BOOST_CLASS_EXPORT_KEY (::libs::events_base::runtime::RuntimeEvent);
