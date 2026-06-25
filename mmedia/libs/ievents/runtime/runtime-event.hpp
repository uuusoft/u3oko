#pragma once
/**
\file       runtime-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime
{
/// Базовый класс всех событий системы с временной меткой
class RuntimeEvent : virtual public TimedEvent, virtual public OpsStatusEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (std::int32_t) {};
  };

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (RuntimeEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (RuntimeEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (RuntimeEvent)

  explicit RuntimeEvent (const Acessor& = Acessor (0));
  virtual ~RuntimeEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/runtime/runtime-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  protected:
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  // internal types
  // U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  //  ievents::TimedEvent overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::ievents::runtime

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::RuntimeEvent);
