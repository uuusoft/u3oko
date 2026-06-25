#pragma once
/**
\file       interf-base-id-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       19.07.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::interf
{
/// Сообщение с интерфейсом для идентификации источника данных
class InterfBaseIdEvent : public BaseInterfEvent
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
  using impl_ptr_type = ::libs::ievents::runtime::interf::interfaces::IBaseId::weak_ptr;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (InterfBaseIdEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (InterfBaseIdEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (InterfBaseIdEvent)

  explicit InterfBaseIdEvent (const Acessor& = Acessor (0), const impl_ptr_type& = impl_ptr_type ());
  virtual ~InterfBaseIdEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/runtime/interf/interf-base-id-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  impl_ptr_type get_interface ();
  void          set_interface (const impl_ptr_type&);

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (BaseInterfEvent)

  impl_ptr_type impl_;   //<

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents::runtime::interf

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::interf::InterfBaseIdEvent);
#endif
