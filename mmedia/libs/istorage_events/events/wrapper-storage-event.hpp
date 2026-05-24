#pragma once
/**
\file       wrapper-http-event.hpp
\date       21.07.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

  virtual ~WrapperStorageEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/istorage_events/events/wrapper-storage-event";
    return ret;
  }

  ::libs::events::IEvent::ptr get_msg () const;
  void                        set_msg (::libs::events::IEvent::ptr&);

  protected:
  ::libs::events::IEvent::ptr int_;   //< событие, для которого производится синхронизация

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::istorage_events::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::WrapperStorageEvent);
