/**
\file       time-point.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       22.05.2022
\project    u3_helpers_lib
*/
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
  ::boost::json::value& jv,
  const TimePoint&      src)
{
  jv = { "time", std::chrono::system_clock::to_time_t (src.get_time ()) };
}


TimePoint
tag_invoke (
  ::boost::json::value_to_tag< TimePoint >,
  const ::boost::json::value& jv)
{
  const auto      raw_time = ::libs::helpers::json::get_int64 (jv.at ("time"));
  const TimePoint ret (::std::chrono::system_clock::from_time_t (raw_time));
  return ret;
}
}   // namespace libs::helpers::time
