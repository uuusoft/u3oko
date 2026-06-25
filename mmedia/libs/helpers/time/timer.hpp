#pragma once
/**
\file       timer.hpp
\author     Erashov Anton erashov2026@proton.me
\date       11.05.2022
\project    u3_helpers_lib
*/

namespace libs::helpers::time
{
class Timer final
{
  public:
  // ext types
  using clock_type = std::chrono::high_resolution_clock;
  using time_type  = std::chrono::milliseconds;

  U3_HELPER_DISABLE_ACOPY_TYPE (Timer)

  Timer ()  = default;
  ~Timer () = default;

  auto
  get_time () -> time_type const
  {
    auto res = clock_type::now () - begin_time_;
    return std::chrono::duration_cast< time_type > (res);
  }

  private:
  clock_type::time_point begin_time_ = clock_type::now ();   //<
};
}   // namespace libs::helpers::time
