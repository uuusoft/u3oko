#pragma once
/**
\file       sync-objs-group.hpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::control
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
}   // namespace libs::ievents::runtime::control

BOOST_CLASS_EXPORT_KEY (libs::ievents::runtime::control::SyncObjsGroup);
