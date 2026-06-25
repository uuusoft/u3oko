#pragma once
/**
\file       libs-link-time-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_link
*/

namespace libs::link::consts
{
#ifdef U3_CNTRL_DEBUG
constexpr std::int32_t ms_send_msg_max_wait = 3 * 60 * 1000;   //< 3 min
#else
constexpr std::int32_t ms_send_msg_max_wait = 1 * 15 * 1000;   //< 15 sec
#endif

constexpr std::int32_t max_count_msgs = 1 * 1024;           //< Максимальное количество сообщений в очередях передачи
constexpr std::int32_t max_size_msg   = 10 * 1024 * 1024;   //< Максимальный размер сообщения в байтах

#if defined(U3_OS_WIN32_DESKTOP) || defined(U3_OS_GNU_LINUX) || defined(U3_OS_MACX_DESKTOP)
constexpr std::int32_t size_shared_mem_bytes           = 1024 * 1024 * 1024;
constexpr std::int32_t ms_wait_delay_recv_msg          = 1;
constexpr std::int32_t ms_wait_delay_special_msg_cycle = 0;
#elif defined(U3_OS_RASPBERRY)
constexpr std::int32_t size_shared_mem_bytes           = 256 * 1024 * 1024;
constexpr std::int32_t ms_wait_delay_recv_msg          = 1;
constexpr std::int32_t ms_wait_delay_special_msg_cycle = 0;
#elif defined(U3_OS_ORANGE_PI)
constexpr std::int32_t size_shared_mem_bytes           = 256 * 1024 * 1024;
constexpr std::int32_t ms_wait_delay_recv_msg          = 1;
constexpr std::int32_t ms_wait_delay_special_msg_cycle = 0;
#elif defined(U3_OS_ANDROID)
constexpr std::int32_t size_shared_mem_bytes           = 128 * 1024 * 1024;
constexpr std::int32_t ms_wait_delay_recv_msg          = 1;
constexpr std::int32_t ms_wait_delay_special_msg_cycle = 1;
#else
#  error select OS
#endif
}   // namespace libs::link::consts
