#pragma once
/**
\file       interf-codec-image-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::interf
{
/// Сообщение с интерфейсом для сжатия изображения
class InterfCodecImageEvent : public BaseInterfEvent
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
  using impl_ptr_type = libs::ievents::runtime::interf::interfaces::ICodecImage::weak_ptr;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (InterfCodecImageEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (InterfCodecImageEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (InterfCodecImageEvent)

  explicit InterfCodecImageEvent (const Acessor& = Acessor (0), const impl_ptr_type& = impl_ptr_type ());
  virtual ~InterfCodecImageEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/runtime/interf/interf-codec-image-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  impl_ptr_type get_interface ();
  void          set_interface (const impl_ptr_type&);

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (BaseInterfEvent)

  impl_ptr_type impl_;   //<

  //  BaseInterfEvent overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents::runtime::interf

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::interf::InterfCodecImageEvent);
#endif
