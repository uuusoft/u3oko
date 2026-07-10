#pragma once
/**
\file       bufs-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::mem
{
/// Событие-уведомление с буферами под/c данными
class BufsEvent : public RuntimeEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  using events_type = std::list< IEvent::ptr >;

  U3_ADD_POINTERS_TO_SELF (BufsEvent)
  U3_ADD_MAKE_SHARED_THIS (BufsEvent)
  U3_ADD_DELETE_MOVE_COPY (BufsEvent)

  explicit BufsEvent (const Acessor& = Acessor (0));
  explicit BufsEvent (const Acessor&, ::libs::bufs::Bufs::ptr& buf, std::list< IEvent::ptr >* events);
  virtual ~BufsEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/runtime/mem/bufs-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_buf () -> ::libs::bufs::Bufs::ptr&;
  auto set_buf (::libs::bufs::Bufs::ptr&) -> void;
  auto get_events () -> events_type*;
  auto set_events (events_type*) -> void;

  private:
  U3_ADD_SUPER_CLASS (RuntimeEvent)

  ::libs::bufs::Bufs::ptr buf_;                //< Буфер с данными, связанный с событием
  events_type*            events_ = nullptr;   //< Список событий, связанный с буфером

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_base::runtime::mem

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
BOOST_CLASS_EXPORT_KEY (::libs::events_base::runtime::mem::BufsEvent);
#endif
