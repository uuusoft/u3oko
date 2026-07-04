#pragma once
/**
\file       mouse-button-down-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/

namespace libs::events_gui::events
{
class MouseButtonDownEvent : public BaseGUIEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (MouseButtonDownEvent)
  U3_ADD_MAKE_SHARED_THIS (MouseButtonDownEvent)
  U3_ADD_DELETE_MOVE_COPY (MouseButtonDownEvent)

  explicit MouseButtonDownEvent (
    const Acessor&              = Acessor (0),
    const TypeMouseButton& type = TypeMouseButton (),
    utils::IPos::ptr       pos  = utils::IPos::ptr ());

  virtual ~MouseButtonDownEvent ();

  virtual TypeEvents get_type () const override;

  TypeMouseButton  get_type_button () const;
  void             set_type_button (const TypeMouseButton&);
  utils::IPos::ptr get_pos () const;
  void             set_pos (const utils::IPos::ptr&);

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_gui/events/props/mouse-button-down-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  private:
  U3_ADD_SUPER_CLASS (::libs::events_gui::events::BaseGUIEvent)

  TypeMouseButton  type_;   //<
  utils::IPos::ptr pos_;    //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_gui::events

BOOST_CLASS_EXPORT_KEY (::libs::events_gui::events::MouseButtonDownEvent);
