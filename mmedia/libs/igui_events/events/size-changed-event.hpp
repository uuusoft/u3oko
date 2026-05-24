#pragma once
/**
\file       size-changed-event.hpp
\date       01.01.2017
\project    uuu_igui_evenets
*/

namespace libs::igui_events::events
{
class SizeChangedEvent : public BaseGUIEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (SizeChangedEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (SizeChangedEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (SizeChangedEvent)

  explicit SizeChangedEvent (
    const Acessor&                                     = Acessor (0),
    const ::libs::igui_events::utils::ISize::ptr& size = ::libs::igui_events::utils::ISize::ptr ());

  virtual ~SizeChangedEvent ();

  virtual TypeEvents get_type () const override;

  ::libs::igui_events::utils::ISize::ptr get_size () const;
  void                                   set_size (const ::libs::igui_events::utils::ISize::ptr&);

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/igui_events/events/props/size-changed-event";
    return ret;
  }

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::igui_events::events::BaseGUIEvent)

  ::libs::igui_events::utils::ISize::ptr size_;   //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_KEY (::libs::igui_events::events::SizeChangedEvent);
