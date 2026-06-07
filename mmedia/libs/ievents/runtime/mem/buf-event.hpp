#pragma once
/**
\file       buf-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::mem
{
/// Событие-уведомление с буферами под/c данными
class BuffEvent : public RuntimeEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BuffEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BuffEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (BuffEvent)

  BuffEvent (const Acessor& = Acessor (0));
  explicit BuffEvent (::utils::dbufs::video::IVideoBuf::cptr& buf);
  virtual ~BuffEvent () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/runtime/mem/buf-event";
    return ret;
  }

  ::utils::dbufs::video::IVideoBuf::ptr& get_buf ();

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent)

  ::utils::dbufs::video::IVideoBuf::ptr buf_;   //< Буфер с данными, связанный с событием

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual void copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::runtime::mem

#ifdef U3_FAKE_DISABLE
BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::mem::BuffEvent);
#endif
