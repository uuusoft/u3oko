#pragma once
/**
\file       wrapper-http-event.hpp
\date       21.07.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_istorage_events
*/

namespace libs::istorage_events::events
{
/// Класс событие для обертки другого события с целью указания модуля-назначения в виде storage сервера
class WrapperStorageEvent : public BaseStorageEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (WrapperStorageEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (WrapperStorageEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (WrapperStorageEvent)

  explicit WrapperStorageEvent (
    const Acessor&                  = Acessor (0),
    ::libs::events::IEvent::ptr msg = ::libs::events::IEvent::ptr ());

  virtual ~WrapperStorageEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/istorage_events/events/wrapper-storage-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_msg () const -> ::libs::events::IEvent::ptr;
  auto set_msg (::libs::events::IEvent::ptr&) -> void;

  protected:
  ::libs::events::IEvent::ptr int_;   //< событие, для которого производится синхронизация

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::istorage_events::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::WrapperStorageEvent);
