/**
\file       timer.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       11.05.2022
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "timer.hpp"

namespace libs::helpers::time
{
Timer::Timer () :
  begin_time_ (clock_type::now ())
{
}


Timer::time_type
Timer::get_time () const
{
  auto res = clock_type::now () - begin_time_;
  return std::chrono::duration_cast< time_type > (res);
}
}   // namespace libs::helpers::time
