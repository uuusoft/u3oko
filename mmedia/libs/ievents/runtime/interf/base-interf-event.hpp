#pragma once
/**
\file       base-interf-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::interf
{
class BaseInterfEvent : public RuntimeEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseInterfEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseInterfEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (BaseInterfEvent)

  explicit BaseInterfEvent (const Acessor& = Acessor (0));
  virtual ~BaseInterfEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/runtime/interf/base-interf-event";
    return ret;
  }

  void set_active (bool enable);
  bool is_active () const;
  void set_available (bool enable);
  bool is_available () const;

  protected:
  //  ievents::Event overrides
  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  //  internal typess
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent)

  bool active_;      //<
  bool available_;   //<

  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
};
}   // namespace libs::ievents::runtime::interf

#if 0
BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::interf::BaseInterfEvent);
#endif
