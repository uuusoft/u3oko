#pragma once
/**
\file   CVideoMatrixProp.hpp
\author   Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date   01.01.2017

\project  u3_ievents_lib
*/

// old shit
namespace libs
{
namespace ievents
{
namespace props
{
namespace videos
{
namespace generics
{
namespace matrix
{
#ifdef U3_FAKE_DISABLE
class CVideoMatrixProp : public ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  public:
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (CVideoMatrixProp)
  U3_HELPER_DISABLE_ACOPY_TYPE ()

  CVideoMatrixProp ();

  virtual ~CVideoMatrixProp ()
  {
  }


  bool        enable_;
  int         koeff_;
  int         bound_;
  bool        change_color_;
  bool        replicate_images_;
  std::string folder_;


  protected:
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_int (const ::pugi::xml_named_node_iterator& node) override;
  virtual void                        copy_int (const IEvent::ptr& src) override;


  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};
#endif
}   // namespace matrix
}   // namespace generics
}   // namespace videos
}   // namespace props
}   // namespace ievents
}   // namespace libs

// BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::matrix::CVideoMatrixProp);
