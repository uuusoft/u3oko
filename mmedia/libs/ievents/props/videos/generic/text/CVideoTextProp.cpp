/**
\file     CVideoTextProp.cpp
\author   Erashov Anton erashov2026@proton.me
\date     01.01.2017
\project  u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "CVideoTextProp.hpp"

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
namespace text
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
CVideoTextProp::CVideoTextProp () : enable_ (false)
{
  property_name_ = "libs/ievents/props/videos/generic/text/CVideoTextProp";
  type_id_       = index_type ({ 0x15, 0x11, 0x0d, 0xb5, 0xec, 0x00, 0x46, 0xf5, 0x9d, 0x4c, 0x33, 0x4c, 0x62, 0x3f, 0x5a, 0x4c });
}


::libs::events::IEvent::ptr
CVideoTextProp::clone_int (const ::libs::events::Deeps& deep) const
{
  if (::libs::events::Deeps::empty == deep)
  {
    return std::m1ake_shared< CVideoTextProp > ();
  }

  return std::m1ake_shared< CVideoTextProp > (*this);
}


template< class Archive >
void
CVideoTextProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (enable_);

  return;
}
#endif
}   // namespace text
}   // namespace generics
}   // namespace videos
}   // namespace props
}   // namespace ievents
}   // namespace libs

// BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::props::videos::generic::text::CVideoTextProp );
////BOOST_CLASS_EXPORT_KEY ();
// U3_BOOST_SERIALIZE_ALL_ARCHIVES( ::libs::ievents::props::videos::generic::text::CVideoTextProp );
