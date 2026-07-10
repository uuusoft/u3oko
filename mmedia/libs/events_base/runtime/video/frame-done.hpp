#pragma once
/**
\file       frame-done.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::video
{
/// Событие-уведомление об завершении обработки одного кадра с данными
class FrameDone : public RuntimeEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (FrameDone)
  U3_ADD_MAKE_SHARED_THIS (FrameDone)
  U3_ADD_DELETE_MOVE_COPY (FrameDone)

  explicit FrameDone (const Acessor& = Acessor (0));
  virtual ~FrameDone () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/runtime/video/frame-done";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::runtime::RuntimeEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_base::runtime::video

BOOST_CLASS_EXPORT_KEY (::libs::events_base::runtime::video::FrameDone);
