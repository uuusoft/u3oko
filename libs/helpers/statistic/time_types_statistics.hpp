//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       time_types_statistics.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Объявление базовых типов статистики.
*/
#ifndef USE_RDTSC_TIMER
//# define USE_RDTSC_TIMER
#endif

#ifndef USE_BOOST_TIMER
#define USE_BOOST_TIMER
#endif

namespace libs { namespace helpers { namespace statistic {

#if defined(USE_RDTSC_TIMER)

using time_type       = unsigned long long;
using duration_type   = unsigned long long;
using count_time_type = unsigned long long;

#define UUU_GET_CURRENT_TIME __rdtsc ()

#elif defined(USE_BOOST_TIMER)

using time_type       = boost::posix_time::ptime;
using duration_type   = boost::posix_time::microsec_clock::time_duration_type;
using count_time_type = boost::posix_time::microseconds;

#define UUU_GET_CURRENT_TIME boost::posix_time::microsec_clock::universal_time ()

#else

using time_type       = std::chrono::system_clock::time_point;
using duration_type   = std::chrono::posix_time::microsec_clock::time_duration_type;
using count_time_type = std::chrono::posix_time::microseconds;

#define UUU_GET_CURRENT_TIME std::chrono::posix_time::microsec_clock::universal_time ()

#endif

}}}      // namespace libs::helpers::statistic
