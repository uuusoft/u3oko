#pragma once
/**
\file       base-http-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ihttp_events
*/

namespace libs::ihttp_events::events
{
/// Базовый класс для событий подсистемы "http сервер"
class BaseHttpEvent : public ::libs::ievents::TimedEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseHttpEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseHttpEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (BaseHttpEvent)

  BaseHttpEvent (const Acessor& = Acessor (0));
  virtual ~BaseHttpEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ihttp_events/events/base-http-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  protected:
  //  BaseHttpEvent overrides
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  //  BaseHttpEvent overrides
  // virtual void load_int( const ::pugi::xml_named_node_iterator& prop ) override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::ihttp_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ihttp_events::events::BaseHttpEvent);
