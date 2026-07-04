#pragma once
/**
\file       expanded-times-types.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/
#ifndef U3_RDTSC_TIMER
// # define U3_RDTSC_TIMER
#endif

#ifndef U3_USE_BOOST_TIMER
#  define U3_USE_BOOST_TIMER
#endif

namespace libs::utility::statistic
{
#ifdef U3_RDTSC_TIMER

using time_type       = std::uint64_t;
using duration_type   = std::uint64_t;
using count_time_type = std::uint64_t;

#  define U3_GET_CURRENT_TIME __rdtsc ()

#elif defined(U3_USE_BOOST_TIMER)

using time_type       = boost::posix_time::ptime;
using u3_clock_type   = boost::posix_time::microsec_clock;
using duration_type   = u3_clock_type::time_duration_type;
using count_time_type = boost::posix_time::microseconds;

#  define U3_GET_CURRENT_TIME ::libs::utility::statistic::u3_clock_type::universal_time ()

#else

using time_type       = std::chrono::system_clock::time_point;
using u3_clock_type   = std::chrono::high_resolution_clock;
using duration_type   = u3_clock_type::duration;
using count_time_type = std::chrono::microseconds;

#  define U3_GET_CURRENT_TIME ::libs::utility::statistic::u3_clock_type::universal_time ()

#endif
}   // namespace libs::utility::statistic
