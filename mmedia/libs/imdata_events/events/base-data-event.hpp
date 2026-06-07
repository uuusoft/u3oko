#pragma once
/**
\file       base-data-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_imdata_events
\brief      Объявление базового класса события модуля обработки данных
*/

namespace libs::imdata_events::events
{
/// Базовое событие для подсистемы обработки данных
/// Является меткой, с помощью которой события перенаправляются центральным модулем в модуль подсистемы обработки данных
class BaseDataEvent : public ::libs::ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (std::int32_t) {};
  };

  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseDataEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseDataEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (BaseDataEvent)

  BaseDataEvent (const Acessor& = Acessor (0));
  virtual ~BaseDataEvent () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/imdata_events/events/base-data-event";
    return ret;
  }

  protected:
  //  ::libs::ievents::Event overrides
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::BaseDataEvent);
