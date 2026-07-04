/**
\file       CVideoMatrixProp.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "CVideoMatrixProp.hpp"

// old shit
namespace libs::events_base::props::videos::generics::matrix
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
CVideoMatrixProp::CVideoMatrixProp () :
  enable_ (false),
  koeff_ (255),
  bound_ (80),
  change_color_ (true),
  replicate_images_ (true)
{
  property_name_ = "libs/events_base/props/videos/generic/matrix/CVideoMatrixProp";

  type_id_ = index_type ({ 0xeb, 0xae, 0x6c, 0x56, 0x8f, 0x03, 0x4e, 0x6f, 0xab, 0x23, 0x55, 0x4e, 0x43, 0x9c, 0x18, 0x85 });
}


::libs::events::IEvent::ptr
CVideoMatrixProp::clone_int (const ::libs::events::Deeps& deep) const
{
  if (::libs::events::Deeps::empty == deep)
  {
    return std::m1ake_shared< CVideoMatrixProp > ();
  }

  return std::m1ake_shared< CVideoMatrixProp > (*this);
}


template< class Archive >
void
CVideoMatrixProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZE_MAKE_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (enable_);
  ar& BOOST_SERIALIZATION_NVP (koeff_);
  ar& BOOST_SERIALIZATION_NVP (bound_);
  ar& BOOST_SERIALIZATION_NVP (change_color_);
  ar& BOOST_SERIALIZATION_NVP (replicate_images_);
  ar& BOOST_SERIALIZATION_NVP (folder_);
  return;
}
#endif
}   // namespace libs::events_base::props::videos::generics::matrix

// BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::events_base::props::videos::generic::matrix::CVideoMatrixProp );
////BOOST_CLASS_EXPORT_KEY ();
// U3_BOOST_ADD_SERIALIZE_ARCH( ::libs::events_base::props::videos::generic::matrix::CVideoMatrixProp );
