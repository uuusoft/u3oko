/**
\file       time-point.cpp
\author     Erashov Anton erashov2026@proton.me
\date       22.05.2022
\project    u3_helpers_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "time-point.hpp"

namespace libs::helpers::time
{
TimePoint::TimePoint (const time_point& now) :
  time_ (now)
{
}


TimePoint::time_point
TimePoint::get_time () const
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
  // jvs = { "time", std::chrono::system_clock::to_time_t (src.get_time ()) };
  jvs = U3_CAST_INT64 (std::chrono::system_clock::to_time_t (src.get_time ()));
}


TimePoint
tag_invoke (
  ::boost::json::value_to_tag< TimePoint >,
  const ::boost::json::value& jvs)
{
  // auto& obj = jvs.as_object();
  // const auto      raw_time = ::libs::helpers::json::get_int64 (jvs.at ("time"));
  const auto      raw_time = ::libs::helpers::json::get_int64 (jvs);
  const TimePoint ret (::std::chrono::system_clock::from_time_t (raw_time));
  return ret;
}
}   // namespace libs::helpers::time
