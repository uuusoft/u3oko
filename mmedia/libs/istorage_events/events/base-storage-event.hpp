#pragma once
/**
\file       base-http-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       21.07.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events::events
{
/// Базовый класс для событий подсистемы "storage сервер"
class BaseStorageEvent : public ::libs::ievents::TimedEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseStorageEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseStorageEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (BaseStorageEvent)

  explicit BaseStorageEvent (const Acessor& = Acessor (0));
  virtual ~BaseStorageEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/istorage_events/events/base-storage-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  protected:
  //  ievents::Event overrides
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::BaseStorageEvent);
