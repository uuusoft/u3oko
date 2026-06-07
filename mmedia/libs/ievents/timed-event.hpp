#pragma once
/**
\file       timed-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents
{
/// Базовый класс всех событий системы с временной меткой
class TimedEvent : public ievents::Event
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

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/timed-event";
    return ret;
  }

  boost::posix_time::ptime get_time () const;

  protected:
  boost::posix_time::ptime time_;   //<

  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
};
}   // namespace libs::ievents

BOOST_CLASS_EXPORT_KEY (::libs::ievents::TimedEvent);
