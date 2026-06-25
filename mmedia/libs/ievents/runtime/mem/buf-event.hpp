#pragma once
/**
\file       buf-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::mem
{
/// Событие-уведомление с буферами под/c данными
class BuffEvent : public RuntimeEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BuffEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BuffEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (BuffEvent)

  BuffEvent (const Acessor& = Acessor (0));
  explicit BuffEvent (::utils::dbufs::video::IVideoBuf::cptr& buf);
  virtual ~BuffEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/runtime/mem/buf-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  ::utils::dbufs::video::IVideoBuf::ptr& get_buf ();

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent)

  ::utils::dbufs::video::IVideoBuf::ptr buf_;   //< Буфер с данными, связанный с событием

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents::runtime::mem

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::mem::BuffEvent);
#endif
