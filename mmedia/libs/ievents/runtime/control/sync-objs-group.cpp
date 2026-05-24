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
SyncObjsGroup::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (time_);
  // ar& BOOST_SERIALIZATION_NVP (time_point_);
  ar& BOOST_SERIALIZATION_NVP (action_);
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const SyncObjsGroup& src)
{
#if 0
  //? ? ?
  jv = {
    { "time", src.time_ },
    { "time_point", src.time_point_ },
    { "action", src.action_ }
  };
#endif
}


SyncObjsGroup
tag_invoke (::boost::json::value_to_tag< SyncObjsGroup >, const ::boost::json::value& jv)
{
  SyncObjsGroup ret;
#if 0
  ret.time_       = jv.at ("time").as_string ();
  ret.time_point_ = ::libs::helpers::json::get_uint32 (jv.at ("time_point"));
  ret.action_     = ::libs::helpers::json::get_uint32 (jv.at ("action"));
#endif
  return ret;
}
}   // namespace libs::ievents::runtime::control

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::control::SyncObjsGroup);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::control::SyncObjsGroup);
