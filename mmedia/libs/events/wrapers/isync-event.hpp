#pragma once
/**
\file       isync-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
\brief      Объявление события синхронизации пересылки другого события
*/

namespace libs::events
{
/// Событие синхронизации
/// Используется как флаг синхронности (требуется ответ на вложенное событие)
class ISyncEvent : public IWrapBaseEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (ISyncEvent)
  U3_ADD_MAKE_SHARED_THIS (ISyncEvent)
  U3_ADD_DELETE_MOVE_COPY (ISyncEvent)

  explicit ISyncEvent (const Acessor& = Acessor (0), IEvent::ptr = IEvent::ptr ());
  virtual ~ISyncEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events/isync-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  protected:
  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps& deep) const -> IEvent::ptr override;
  virtual void copy_int (const IEvent::craw_ptr) override;

  private:
  U3_ADD_SUPER_CLASS (IWrapBaseEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::ISyncEvent);
