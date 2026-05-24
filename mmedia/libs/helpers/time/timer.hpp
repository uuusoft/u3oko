#pragma once
/**
\file       timer.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

  Timer ();
  time_type get_time () const;

  private:
  clock_type::time_point begin_time_;   //<
};
}   // namespace libs::helpers::time
