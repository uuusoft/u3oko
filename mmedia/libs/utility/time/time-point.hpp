#pragma once
/**
\file       time-point.hpp
\author     Erashov Anton erashov2026@proton.me
\date       22.05.2022
\project    u3_helpers_lib
*/

namespace libs::utility::time
{
class TimePoint final
{
  public:
  // ext types
  using clock_type = std::chrono::system_clock;
  using time_point = std::chrono::time_point< clock_type >;

  explicit TimePoint (const time_point& now = std::chrono::system_clock::now ());

  time_point get_time () const;
  void       set_time (const time_point& time);

  private:
  time_point time_;   //<
};

void      tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const TimePoint& src);
TimePoint tag_invoke (::boost::json::value_to_tag< TimePoint >, const ::boost::json::value& jvs);
}   // namespace libs::utility::time
