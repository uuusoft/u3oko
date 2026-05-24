#pragma once
/**
\file       base-http-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  virtual ~BaseStorageEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/istorage_events/events/base-storage-event";
    return ret;
  }

  protected:
  //  ievents::Event overrides
  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
};
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::BaseStorageEvent);
