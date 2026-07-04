#pragma once
/**
\file   CVideoMatrixProp.hpp
\author   Erashov Anton erashov2026@proton.me
\date   01.01.2017
\project  u3_events_base_lib
*/

// old shit
namespace libs::events_base::props::videos::generics::matrix
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
class CVideoMatrixProp : virtual public events_base::Event
{
  friend class boost::serialization::access;

  public:
  U3_ADD_POINTERS_TO_SELF (CVideoMatrixProp)
  U3_ADD_DELETE_MOVE_COPY ()

  CVideoMatrixProp ();
  virtual ~CVideoMatrixProp () = default;

  bool        enable_;
  int         koeff_;
  int         bound_;
  bool        change_color_;
  bool        replicate_images_;
  std::string folder_;

  protected:
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual void load_int (const ::pugi::xml_named_node_iterator& node) override;
  virtual void copy_int (const IEvent::ptr&) override;

  private:
  U3_ADD_SUPER_CLASS (events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};
#endif
}   // namespace libs::events_base::props::videos::generics::matrix

// BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::matrix::CVideoMatrixProp);
