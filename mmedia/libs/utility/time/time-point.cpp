/**
\file       time-point.cpp
\author     Erashov Anton erashov2026@proton.me
\date       22.05.2022
\project    u3_helpers_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../utility-lib-includes_int.hpp"
#include "time-point.hpp"

namespace libs::utility::time
{
TimePoint::TimePoint (const time_point& now) :
  time_ (now)
{
}


auto
TimePoint::get_time () const -> TimePoint::time_point
{
  return time_;
}


void
TimePoint::set_time (const time_point& time)
{
  time_ = time;
}


void
tag_invoke (
  ::boost::json::value_from_tag,
  ::boost::json::value& jvs,
  const TimePoint&      src)
{
  jvs = U3_CAST_INT64 (std::chrono::system_clock::to_time_t (src.get_time ()));
}


auto
tag_invoke (
  ::boost::json::value_to_tag< TimePoint >,
  const ::boost::json::value& jvs) -> TimePoint
{
  const auto      raw_time = ::libs::utility::json::get_int64 (jvs);
  const TimePoint ret (::std::chrono::system_clock::from_time_t (raw_time));
  return ret;
}
}   // namespace libs::utility::time
