#pragma once
/**
\file       ianswer-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_events
*/

namespace libs::events
{
/// Событие запроса
/// Используется как флаг запроса (требуется ответ в виде вложенного события)
class IAnswerEvent : public IWrapBaseEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IAnswerEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (IAnswerEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (IAnswerEvent)

  explicit IAnswerEvent (const Acessor& = Acessor (0), IEvent::ptr = IEvent::ptr ());
  virtual ~IAnswerEvent () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/events/ianswer-event";
    return ret;
  }

  protected:
  virtual IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void        copy_int (const IEvent::craw_ptr src) override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (IWrapBaseEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::IAnswerEvent);
