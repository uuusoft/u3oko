#pragma once
/**
\file   CVideoSharperProp.hpp
\author   Erashov Anton erashov2026@proton.me
\date   01.01.2017
\project  u3_events_base_lib
*/

// old shit
namespace libs::events_base::props::videos::generics::sharper
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
struct EventBufs : public ::libs::events::buf::E - ventBufsInfo {
  friend class boost::serialization::access;

  public:
  EventBufs () = default;

  float koeff_ = 0.0F;

  protected:
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual void copy_int (const IEvent::ptr&) override;
  virtual void
  load_int (const ::pugi::xml_named_node_iterator& node) override
  {
    check ();
    return;
  }

  private:
  U3_ADD_SUPER_CLASS (::libs::events::buf::EventBufs)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};


class CVideoSharperProp : virtual public events_base::Event
{
  public:
  U3_ADD_POINTERS_TO_SELF (CVideoSharperProp)

  CVideoSharperProp ();
  virtual ~CVideoSharperProp () = default;

  std::vector< EventBufs > bufs_;

  protected:
  // virtual void load_int (const ::pugi::xml_named_node_iterator& node) override;

  private:
  U3_ADD_SUPER_CLASS (events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
#endif
}   // namespace libs::events_base::props::videos::generics::sharper

// BOOST_CLASS_EXPORT_KEY( ::libs::events_base::props::videos::generic::sharper::EventBufs );
// BOOST_CLASS_EXPORT_KEY( ::libs::events_base::props::videos::generic::sharper::CVideoSharperProp );
