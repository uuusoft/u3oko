#pragma once
/**
\file   CVideoTextProp.hpp
\author   Erashov Anton erashov2026@proton.me
\date   01.01.2017

\project  u3_ievents_lib
*/

// old shit
namespace libs::ievents::props::videos::generics::text
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
class CVideoTextProp : virtual public ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  public:
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (CVideoTextProp)

  CVideoTextProp ();

  virtual ~CVideoTextProp ()
  {
  }

  bool enable_;

  protected:
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual void copy_int (const IEvent::ptr& src) override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
#endif
}   // namespace libs::ievents::props::videos::generics::text

// BOOST_CLASS_EXPORT_KEY( ::libs::ievents::props::videos::generic::text::CVideoTextProp );
