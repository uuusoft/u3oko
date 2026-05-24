#pragma once
/**
\file       base-error-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::error
{
/// Базовое событие-уведомление об ошибке
/// Может быть получено в ответ на неверное синхронное событие, как сигнал о неверной ситуации
class BaseErrorEvent : public RuntimeEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseErrorEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseErrorEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (BaseErrorEvent)

  explicit BaseErrorEvent (const Acessor& = Acessor (0), const std::string& info = std::string ());
  virtual ~BaseErrorEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/runtime/error/base-error-event";
    return ret;
  }

  const std::string& what () const;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::runtime::RuntimeEvent)

  std::string info_;   //< Текстовое описание ошибки

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::runtime::error

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::error::BaseErrorEvent);
