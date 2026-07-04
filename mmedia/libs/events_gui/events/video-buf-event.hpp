#pragma once
/**
\file       video-buf-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/

namespace libs::events_gui::events
{
//  syn
typedef ::libs::bufs::Bufs Bufs;

class VideoBufEvent : public BaseGUIEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (VideoBufEvent)
  U3_ADD_MAKE_SHARED_THIS (VideoBufEvent)
  U3_ADD_DELETE_MOVE_COPY (VideoBufEvent)

  explicit VideoBufEvent (const Acessor& = Acessor (0), Bufs::ptr buf = ::libs::bufs::Bufs::ptr (), int id = 0);

  virtual ~VideoBufEvent ();

  virtual TypeEvents get_type () const override;

  const Bufs::ptr get_buf () const;
  void            set_buf (Bufs::ptr&);
  int             get_id () const;
  void            set_id (int);

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_gui/events/props/video-buf-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  private:
  U3_ADD_SUPER_CLASS (::libs::events_gui::events::BaseGUIEvent)

  Bufs::ptr    buf_;   //<
  std::int32_t id_;    //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_gui::events

BOOST_CLASS_EXPORT_KEY (::libs::events_gui::events::VideoBufEvent);
