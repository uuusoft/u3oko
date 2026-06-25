#pragma once
/**
\file       wrapper-http-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ihttp_events
*/

namespace libs::ihttp_events::events
{
/// Класс событие для обертки другого события с целью указания модуля-назначения в виде http сервера
class WrapperHttpEvent : public BaseHttpEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (WrapperHttpEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (WrapperHttpEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (WrapperHttpEvent)

  explicit WrapperHttpEvent (
    const Acessor&                  = Acessor (0),
    ::libs::events::IEvent::ptr msg = ::libs::events::IEvent::ptr ());

  virtual ~WrapperHttpEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ihttp_events/events/wrapper-http-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_msg () const -> ::libs::events::IEvent::ptr;
  auto set_msg (::libs::events::IEvent::ptr& msg) -> void;

  protected:
  ::libs::events::IEvent::ptr int_;   //< событие, для которого производится синхронизация

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  //  BaseHttpEvent overrides
  // virtual void load_int( const ::pugi::xml_named_node_iterator& prop ) override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ihttp_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ihttp_events::events::WrapperHttpEvent);
