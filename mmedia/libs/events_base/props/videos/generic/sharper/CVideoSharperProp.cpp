/**
\file     CVideoSharperProp.cpp
\author   Erashov Anton erashov2026@proton.me
\date     01.01.2017
\project  u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "CVideoSharperProp.hpp"

namespace libs::events_base::props::videos::generics::sharper
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
template< class Archive >
void
EventBufs::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP (super);
  arh& BOOST_SERIALIZATION_NVP (koeff_);
  return;
}


CVideoSharperProp::CVideoSharperProp ()
{
  property_name_ = "libs/events_base/props/videos/generic/sharper/CVideoSharperProp";
  type_id_       = index_type ({ 0xb8, 0x7d, 0xd6, 0x4a, 0x8d, 0x3d, 0x41, 0x5e, 0xa1, 0x80, 0xa6, 0x51, 0x8d, 0xfd, 0x4e, 0x62 });
}


::libs::events::IEvent::ptr
CVideoSharperProp::clone_int (const ::libs::events::Deeps& deep) const
{
  if (::libs::events::Deeps::empty == deep)
  {
    return std::m1ake_shared< CVideoSharperProp > ();
  }

  return std::m1ake_shared< CVideoSharperProp > (*this);
}
#endif
}   // namespace libs::events_base::props::videos::generics::sharper

// BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::events_base::props::videos::generic::sharper::EventBufs );
////BOOST_CLASS_EXPORT_KEY ();
// U3_BOOST_ADD_SERIALIZE_ARCH( ::libs::events_base::props::videos::generic::sharper::CVideoSharperProp );
