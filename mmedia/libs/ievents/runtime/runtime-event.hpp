#pragma once
/**
\file       runtime-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime
{
/// Базовый класс всех событий системы с временной меткой
class RuntimeEvent : public ievents::TimedEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (std::int32_t) {};
  };

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (RuntimeEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (RuntimeEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (RuntimeEvent)

  explicit RuntimeEvent (const Acessor& = Acessor (0));
  virtual ~RuntimeEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/runtime/runtime-event";
    return ret;
  }

  protected:
  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::TimedEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
  //  ievents::TimedEvent overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
};
}   // namespace libs::ievents::runtime

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::RuntimeEvent);
