#pragma once
/**
\file       video-buf-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    uuu_igui_evenets
*/

namespace libs::igui_events::events
{
//  syn
typedef ::libs::bufs::Bufs Bufs;

class VideoBufEvent : public BaseGUIEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoBufEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoBufEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoBufEvent)

  explicit VideoBufEvent (const Acessor& = Acessor (0), const Bufs::ptr& buf = ::libs::bufs::Bufs::ptr (), int id = 0);

  virtual ~VideoBufEvent ();

  virtual TypeEvents get_type () const override;

  const Bufs::ptr get_buf () const;
  void            set_buf (Bufs::ptr&);
  int             get_id () const;
  void            set_id (int);

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/igui_events/events/props/video-buf-event";
    return ret;
  }

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::igui_events::events::BaseGUIEvent)

  Bufs::ptr    buf_;   //<
  std::int32_t id_;    //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_KEY (::libs::igui_events::events::VideoBufEvent);
