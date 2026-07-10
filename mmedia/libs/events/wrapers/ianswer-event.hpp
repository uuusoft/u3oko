#pragma once
/**
\file       ianswer-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/

namespace libs::events
{
/// Событие запроса
/// Используется как флаг запроса (требуется ответ в виде вложенного события)
class IAnswerEvent : public IWrapBaseEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (IAnswerEvent)
  U3_ADD_MAKE_SHARED_THIS (IAnswerEvent)
  U3_ADD_DELETE_MOVE_COPY (IAnswerEvent)

  explicit IAnswerEvent (const Acessor& = Acessor (0), IEvent::ptr = IEvent::ptr ());
  virtual ~IAnswerEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events/ianswer-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  protected:
  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> IEvent::ptr override;
  virtual void copy_int (const IEvent::craw_ptr) override;

  private:
  U3_ADD_SUPER_CLASS (IWrapBaseEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::IAnswerEvent);
