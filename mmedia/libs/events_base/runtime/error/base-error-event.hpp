#pragma once
/**
\file       base-error-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::error
{
/// Базовое событие-уведомление об ошибке
/// Может быть получено в ответ на неверное синхронное событие, как сигнал о неверной ситуации
class BaseErrorEvent : public RuntimeEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (BaseErrorEvent)
  U3_ADD_MAKE_SHARED_THIS (BaseErrorEvent)
  U3_ADD_DELETE_MOVE_COPY (BaseErrorEvent)

  explicit BaseErrorEvent (const Acessor& = Acessor (0), std::string info = std::string ());
  virtual ~BaseErrorEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/runtime/error/base-error-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  const std::string& what () const;

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::runtime::RuntimeEvent)

  std::string info_;   //< Текстовое описание ошибки

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const ::libs::events::IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_base::runtime::error

BOOST_CLASS_EXPORT_KEY (::libs::events_base::runtime::error::BaseErrorEvent);
