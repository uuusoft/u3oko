#pragma once
/**
\file       base-http-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       21.07.2018
\project    u3_events_storage
*/

namespace libs::events_storage::events
{
/// Базовый класс для событий подсистемы "storage сервер"
class BaseStorageEvent : public ::libs::events_base::TimedEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (BaseStorageEvent)
  U3_ADD_MAKE_SHARED_THIS (BaseStorageEvent)
  U3_ADD_DELETE_MOVE_COPY (BaseStorageEvent)

  explicit BaseStorageEvent (const Acessor& = Acessor (0));
  virtual ~BaseStorageEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_storage/events/base-storage-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  protected:
  //  events_base::Event overrides
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
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_KEY (::libs::events_storage::events::BaseStorageEvent);
