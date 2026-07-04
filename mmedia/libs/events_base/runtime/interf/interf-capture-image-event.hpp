#pragma once
/**
\file       interf-capture-image-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       17.08.2018
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::interf
{
/// Сообщение с интерфейсом для захвата изображения
class InterfCaptureImageEvent : public BaseInterfEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using impl_ptr_type = libs::events_base::runtime::interf::interfaces::ICaptureImage::weak_ptr;

  U3_ADD_POINTERS_TO_SELF (InterfCaptureImageEvent)
  U3_ADD_MAKE_SHARED_THIS (InterfCaptureImageEvent)
  U3_ADD_DELETE_MOVE_COPY (InterfCaptureImageEvent)

  explicit InterfCaptureImageEvent (const Acessor& = Acessor (0), impl_ptr_type = impl_ptr_type ());
  virtual ~InterfCaptureImageEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/runtime/interf/interf-capture-image-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  impl_ptr_type get_interface ();
  void          set_interface (const impl_ptr_type&);

  private:
  U3_ADD_SUPER_CLASS (BaseInterfEvent)

  impl_ptr_type impl_;   //<

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_base::runtime::interf

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
BOOST_CLASS_EXPORT_KEY (::libs::events_base::runtime::interf::InterfCaptureImageEvent);
#endif
