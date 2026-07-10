#pragma once
/**
\file       iwrap-base-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/

namespace libs::events
{
/// Событие синхронизации. Используется как флаг синхронности (требуется ответ на вложенное событие)
class IWrapBaseEvent : public IEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (IWrapBaseEvent)
  U3_ADD_MAKE_SHARED_THIS (IWrapBaseEvent)
  U3_ADD_DELETE_MOVE_COPY (IWrapBaseEvent)

  explicit IWrapBaseEvent (const Acessor& = Acessor (0), IEvent::ptr = IEvent::ptr ());
  virtual ~IWrapBaseEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events/iwrap-base-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_msg () const -> IEvent::ptr;
  auto set_msg (IEvent::ptr&) -> void;

  protected:
  IEvent::ptr int_;   //< Событие, для которого производится синхронизация

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  U3_ADD_SUPER_CLASS (IEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::IWrapBaseEvent);
