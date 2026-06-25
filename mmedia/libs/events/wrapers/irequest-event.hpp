#pragma once
/**
\file       irequest-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/

namespace libs::events
{
/// Событие запроса какого либо другого (вложенного в него) события
/// Используется как флаг запроса (требуется ответ в виде вложенного события)
class IRequestEvent : public IWrapBaseEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IRequestEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (IRequestEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (IRequestEvent)

  explicit IRequestEvent (const Acessor& = Acessor (0), IEvent::ptr = IEvent::ptr ());
  virtual ~IRequestEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events/irequest-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  protected:
  virtual auto clone_int (const ::libs::events::Deeps& deep) const -> IEvent::ptr override;
  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (IWrapBaseEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::IRequestEvent);
