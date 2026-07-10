#pragma once
/**
\file       wrapper-http-event.hpp
\date       21.07.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_storage
*/

namespace libs::events_storage::events
{
/// Класс событие для обертки другого события с целью указания модуля-назначения в виде storage сервера
class WrapperStorageEvent : public BaseStorageEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (WrapperStorageEvent)
  U3_ADD_MAKE_SHARED_THIS (WrapperStorageEvent)
  U3_ADD_DELETE_MOVE_COPY (WrapperStorageEvent)

  explicit WrapperStorageEvent (
    const Acessor&                  = Acessor (0),
    ::libs::events::IEvent::ptr msg = ::libs::events::IEvent::ptr ());

  virtual ~WrapperStorageEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_storage/events/wrapper-storage-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_msg () const -> ::libs::events::IEvent::ptr;
  auto set_msg (::libs::events::IEvent::ptr&) -> void;

  protected:
  ::libs::events::IEvent::ptr int_;   //< событие, для которого производится синхронизация

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_storage::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_KEY (::libs::events_storage::events::WrapperStorageEvent);
