#pragma once
/**
\file       buf-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::mem
{
/// Событие-уведомление с буферами под/c данными
class BuffEvent : public RuntimeEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (BuffEvent)
  U3_ADD_MAKE_SHARED_THIS (BuffEvent)
  U3_ADD_DELETE_MOVE_COPY (BuffEvent)

  BuffEvent (const Acessor& = Acessor (0));
  explicit BuffEvent (::utils::dbufs::video::IVideoBuf::cptr& buf);
  virtual ~BuffEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/runtime/mem/buf-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_buf () -> ::utils::dbufs::video::IVideoBuf::ptr&;

  private:
  U3_ADD_SUPER_CLASS (RuntimeEvent)

  ::utils::dbufs::video::IVideoBuf::ptr buf_;   //< Буфер с данными, связанный с событием

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const ::libs::events::IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_base::runtime::mem

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
BOOST_CLASS_EXPORT_KEY (::libs::events_base::runtime::mem::BuffEvent);
#endif
