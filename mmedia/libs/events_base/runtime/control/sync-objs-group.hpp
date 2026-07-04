#pragma once
/**
\file       sync-objs-group.hpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::control
{
struct SyncObjsGroup {
  using time_point_type = std::chrono::system_clock::time_point;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  SyncTimes   time_   = SyncTimes::realtime;   //<
  SyncActions action_ = SyncActions::empty;    //<
};

void          tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const SyncObjsGroup& src);
SyncObjsGroup tag_invoke (::boost::json::value_to_tag< SyncObjsGroup >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::runtime::control

BOOST_CLASS_EXPORT_KEY (libs::events_base::runtime::control::SyncObjsGroup);
