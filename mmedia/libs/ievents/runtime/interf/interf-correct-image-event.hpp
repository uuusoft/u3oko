#pragma once
/**
\file       interf-correct-image-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::interf
{
/// Сообщение с интерфейсом для коррекции изображения
class InterfCorrectImageEvent : public BaseInterfEvent
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
  using impl_ptr_type = libs::ievents::runtime::interf::interfaces::ICorrectImage::weak_ptr;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (InterfCorrectImageEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (InterfCorrectImageEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (InterfCorrectImageEvent)

  explicit InterfCorrectImageEvent (const Acessor& = Acessor (0), const impl_ptr_type& = impl_ptr_type ());
  virtual ~InterfCorrectImageEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/runtime/interf/interf-correct-image-event";
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

#if 0
BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::interf::InterfCorrectImageEvent);
#endif
