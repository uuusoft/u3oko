#pragma once
/**
\file       mouse-button-up-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_igui_events
*/

namespace libs::igui_events::events
{
class MouseButtonUpEvent : public BaseGUIEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (MouseButtonUpEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MouseButtonUpEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (MouseButtonUpEvent)

  explicit MouseButtonUpEvent (
    const Acessor&               = Acessor (0),
    const TypeMouseButton&  type = TypeMouseButton (),
    const utils::IPos::ptr& pos  = utils::IPos::ptr ());

  virtual ~MouseButtonUpEvent ();

  virtual TypeEvents get_type () const override;

  TypeMouseButton  get_type_button () const;
  void             set_type_button (const TypeMouseButton&);
  utils::IPos::ptr get_pos () const;
  void             set_pos (const utils::IPos::ptr&);

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/igui_events/events/props/mouse-button-up-event";
    return ret;
  }

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::igui_events::events::BaseGUIEvent)

  TypeMouseButton  type_;   //<
  utils::IPos::ptr pos_;    //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_KEY (::libs::igui_events::events::MouseButtonUpEvent);
