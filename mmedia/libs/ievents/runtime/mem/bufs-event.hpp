#pragma once
/**
\file       bufs-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::mem
{
/// Событие-уведомление с буферами под/c данными
class BufsEvent : public RuntimeEvent
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
  using events_type = std::list< IEvent::ptr >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BufsEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BufsEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (BufsEvent)

  explicit BufsEvent (const Acessor& = Acessor (0));
  explicit BufsEvent (const Acessor&, ::libs::bufs::Bufs::ptr& buf, std::list< IEvent::ptr >* events);
  virtual ~BufsEvent () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/runtime/mem/bufs-event";
    return ret;
  }

  ::libs::bufs::Bufs::ptr& get_buf ();
  void                     set_buf (::libs::bufs::Bufs::ptr&);
  events_type*             get_events ();
  void                     set_events (events_type*);

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent)

  ::libs::bufs::Bufs::ptr buf_;      //< Буфер с данными, связанный с событием
  events_type*            events_;   //< Список событий, связанный с буфером

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual void copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::runtime::mem

#ifdef U3_FAKE_DISABLE
BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::mem::BufsEvent);
#endif
