#pragma once
/**
\file   CVideoTextProp.hpp
\author   Erashov Anton erashov2026@proton.me
\date   01.01.2017
\project  u3_events_base_lib
*/

// old shit
namespace libs::events_base::props::videos::generics::text
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
class CVideoTextProp : virtual public events_base::Event
{
  friend class boost::serialization::access;

  public:
  U3_ADD_POINTERS_TO_SELF (CVideoTextProp)

  CVideoTextProp ();
  virtual ~CVideoTextProp () = default;

  bool enable_;

  protected:
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual void copy_int (const IEvent::ptr&) override;

  private:
  U3_ADD_SUPER_CLASS (events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
#endif
}   // namespace libs::events_base::props::videos::generics::text

// BOOST_CLASS_EXPORT_KEY( ::libs::events_base::props::videos::generic::text::CVideoTextProp );
