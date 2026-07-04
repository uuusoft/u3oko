#pragma once
/**
\file       mem-block-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/

namespace libs::events_gui::events
{
//  forward
class CBuffHelper_ResetVideo;

class MemBlockEvent : public BaseGUIEvent
{
  friend class CBuffHelper_ResetVideo;
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (MemBlockEvent)
  U3_ADD_MAKE_SHARED_THIS (MemBlockEvent)
  U3_ADD_DELETE_MOVE_COPY (MemBlockEvent)

  explicit MemBlockEvent (
    const Acessor&                               = Acessor (0),
    const ::libs::link::mem::IBlockFakeMem& hmem = ::libs::link::mem::IBlockFakeMem (),
    std::int32_t                            id   = 0);

  virtual ~MemBlockEvent ();

  virtual TypeEvents get_type () const override;

  ::libs::link::mem::IBlockFakeMem get_hmem ();
  void                             set_hmem (const ::libs::link::mem::IBlockFakeMem&);
  bool                             reset_video (void* pmem) const;
  std::int32_t                     get_id () const;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_gui/events/props/mem-block-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  private:
  U3_ADD_SUPER_CLASS (::libs::events_gui::events::BaseGUIEvent)

  ::libs::link::mem::IBlockFakeMem hmem_;   //<
  std::int32_t                     id_;     //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};


class CBuffHelper_ResetVideo : public ::libs::link::mem::IHandlerMem
{
  public:
  CBuffHelper_ResetVideo (MemBlockEvent* obj) :
    obj_ (obj)
  {
  }

  virtual ~CBuffHelper_ResetVideo () = default;

  virtual bool
  update (void* pmem) const override
  {
    obj_->reset_video (pmem);
    return true;
  }

  private:
  mutable MemBlockEvent* obj_;   //<
};
}   // namespace libs::events_gui::events

BOOST_CLASS_EXPORT_KEY (::libs::events_gui::events::MemBlockEvent);
