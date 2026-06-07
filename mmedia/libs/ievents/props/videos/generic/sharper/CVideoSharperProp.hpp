#pragma once
/**
\file   CVideoSharperProp.hpp
\author   Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date   01.01.2017

\project  u3_ievents_lib
*/

// old shit
namespace libs::ievents::props::videos::generics::sharper
{
#ifdef U3_FAKE_DISABLE
struct EventBufsInfo : public ::libs::events::buf::E - ventBufsInfo {
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  public:
  EventBufsInfo () :
    koeff_ (0.0F)
  {
  }

  float koeff_;


  protected:
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::ptr& src) override;
  virtual void
  load_int (const ::pugi::xml_named_node_iterator& node) override
  {
    check ();
    return;
  }

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::buf::EventBufsInfo)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};


class CVideoSharperProp : public ievents::Event
{
  public:
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (CVideoSharperProp)

  CVideoSharperProp ();

  virtual ~CVideoSharperProp ()
  {
  }


  std::vector< EventBufsInfo > bufs_;


  protected:
  // virtual void load_int (const ::pugi::xml_named_node_iterator& node) override;


  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
#endif
}   // namespace libs::ievents::props::videos::generics::sharper

// BOOST_CLASS_EXPORT_KEY( ::libs::ievents::props::videos::generic::sharper::EventBufsInfo );
// BOOST_CLASS_EXPORT_KEY( ::libs::ievents::props::videos::generic::sharper::CVideoSharperProp );
