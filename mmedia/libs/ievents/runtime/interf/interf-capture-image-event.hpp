#pragma once
/**
\file       interf-capture-image-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       17.08.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::interf
{
/// Сообщение с интерфейсом для захвата изображения
class InterfCaptureImageEvent : public BaseInterfEvent
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
  using impl_ptr_type = libs::ievents::runtime::interf::interfaces::ICaptureImage::weak_ptr;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (InterfCaptureImageEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (InterfCaptureImageEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (InterfCaptureImageEvent)

  explicit InterfCaptureImageEvent (const Acessor& = Acessor (0), const impl_ptr_type& = impl_ptr_type ());
  virtual ~InterfCaptureImageEvent () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/runtime/interf/interf-capture-image-event";
    return ret;
  }

  impl_ptr_type get_interface ();
  void          set_interface (const impl_ptr_type&);

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (BaseInterfEvent)

  impl_ptr_type impl_;   //<

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual void copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::runtime::interf

#ifdef U3_FAKE_DISABLE
BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::interf::InterfCaptureImageEvent);
#endif
