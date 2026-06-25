#pragma once
/**
\file       timed-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents
{
/// Базовый класс всех событий системы с временной меткой
class TimedEvent : virtual public ievents::Event
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (TimedEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (TimedEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (TimedEvent)

  explicit TimedEvent (const Acessor& = Acessor (0));
  virtual ~TimedEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/timed-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  boost::posix_time::ptime get_time () const;

  protected:
  boost::posix_time::ptime time_;   //<

  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
};
}   // namespace libs::ievents

BOOST_CLASS_EXPORT_KEY (::libs::ievents::TimedEvent);
