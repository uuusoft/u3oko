#pragma once
/**
\file       iwrap-base-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_events
*/

namespace libs::events
{
/// Событие синхронизации. Используется как флаг синхронности (требуется ответ на вложенное событие)
class IWrapBaseEvent : public IEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IWrapBaseEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (IWrapBaseEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (IWrapBaseEvent)

  explicit IWrapBaseEvent (const Acessor& = Acessor (0), IEvent::ptr = IEvent::ptr ());
  virtual ~IWrapBaseEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/events/iwrap-base-event";
    return ret;
  }

  IEvent::ptr get_msg () const;
  void        set_msg (IEvent::ptr&);

  protected:
  IEvent::ptr int_;   //< Событие, для которого производится синхронизация

  virtual IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void        load_json_int (const ::boost::json::object& obj) override;
  virtual void        save_json_int (::boost::json::object& obj) const override;
  virtual void        copy_int (const IEvent::craw_ptr src) override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (IEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};
}   // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::IWrapBaseEvent);
