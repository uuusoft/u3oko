/**
\file       sync-objs-group.cpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "sync-objs-group.hpp"

namespace libs::events_base::runtime::control
{
template< class Archive >
void
SyncObjsGroup::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (time_);
  // arh& BOOST_SERIALIZATION_NVP (time_point_);
  arh& BOOST_SERIALIZATION_NVP (action_);
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const SyncObjsGroup& src)
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  jvs = {
    { "time", src.time_ },
    { "time_point", src.time_point_ },
    { "sync_actions", src.action_ }
  };
#endif
}


auto
tag_invoke (::boost::json::value_to_tag< SyncObjsGroup >, const ::boost::json::value& jvs) -> SyncObjsGroup
{
  SyncObjsGroup ret;
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  ret.time_       = jvs.at ("time").as_string ();
  ret.time_point_ = ::libs::utility::json::get_uint32 (jvs.at ("time_point"));
  ret.action_     = ::libs::utility::json::get_uint32 (jvs.at ("sync_actions"));
#endif
  return ret;
}
}   // namespace libs::events_base::runtime::control

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::control::SyncObjsGroup);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::control::SyncObjsGroup);
