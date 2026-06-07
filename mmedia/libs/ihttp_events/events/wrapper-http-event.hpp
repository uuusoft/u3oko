#pragma once
/**
\file       wrapper-http-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ihttp_events/events/wrapper-http-event";
    return ret;
  }

  ::libs::events::IEvent::ptr get_msg () const;
  void                        set_msg (::libs::events::IEvent::ptr& msg);

  protected:
  ::libs::events::IEvent::ptr int_;   //< событие, для которого производится синхронизация

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  //  BaseHttpEvent overrides
  // virtual void load_int( const ::pugi::xml_named_node_iterator& prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ihttp_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ihttp_events::events::WrapperHttpEvent);
