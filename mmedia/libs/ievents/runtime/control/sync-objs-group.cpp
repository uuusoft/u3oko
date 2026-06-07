/**
\file       sync-objs-group.cpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "sync-objs-group.hpp"

namespace libs::ievents::runtime::control
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
#ifdef U3_FAKE_DISABLE
  jvs = {
    { "time", src.time_ },
    { "time_point", src.time_point_ },
    { "action", src.action_ }
  };
#endif
}


SyncObjsGroup
tag_invoke (::boost::json::value_to_tag< SyncObjsGroup >, const ::boost::json::value& jvs)
{
  SyncObjsGroup ret;
#ifdef U3_FAKE_DISABLE
  ret.time_       = jvs.at ("time").as_string ();
  ret.time_point_ = ::libs::helpers::json::get_uint32 (jvs.at ("time_point"));
  ret.action_     = ::libs::helpers::json::get_uint32 (jvs.at ("action"));
#endif
  return ret;
}
}   // namespace libs::ievents::runtime::control

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::control::SyncObjsGroup);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::control::SyncObjsGroup);
