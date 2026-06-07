#pragma once
/**
\file       libs-link-size-vals.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_link
*/

namespace libs::link::consts::size
{
constexpr std::uint32_t buf_all2log    = 1 * 1024 * 1024;
constexpr std::uint32_t buf_all2events = 1 * 1024 * 1024;

constexpr std::uint32_t max_width_one_frame  = 8 * 1024;
constexpr std::uint32_t max_height_one_frame = 8 * 1024;
constexpr std::uint32_t buf_for_one_frame    = max_width_one_frame * max_height_one_frame * 6 + max_width_one_frame * 64;

#ifdef U3_OS_WIN32_DESKTOP

constexpr std::uint32_t buf_appl2gul     = 2 * buf_for_one_frame;
constexpr std::uint32_t buf_appl2appl    = 20 * 1024 * 1024;
constexpr std::uint32_t buf_appl2data    = 20 * 1024 * 1024;
constexpr std::uint32_t buf_appl2http    = 20 * 1024 * 1024;
constexpr std::uint32_t buf_appl2storage = 10 * 1024 * 1024;

#elif defined(U3_OS_GNU_LINUX)

constexpr std::uint32_t buf_appl2gul     = 2 * buf_for_one_frame;
constexpr std::uint32_t buf_appl2appl    = 20 * 1024 * 1024;
constexpr std::uint32_t buf_appl2data    = 20 * 1024 * 1024;
constexpr std::uint32_t buf_appl2http    = 20 * 1024 * 1024;
constexpr std::uint32_t buf_appl2storage = 10 * 1024 * 1024;

#elif defined(U3_OS_RASPBERRY)

constexpr std::uint32_t buf_appl2gul     = 1024 * 1024;
constexpr std::uint32_t buf_appl2appl    = 5 * 1024 * 1024;
constexpr std::uint32_t buf_appl2data    = 5 * 1024 * 1024;
constexpr std::uint32_t buf_appl2http    = 5 * 1024 * 1024;
constexpr std::uint32_t buf_appl2storage = 5 * 1024 * 1024;

#elif defined(U3_OS_ORANGE_PI)

constexpr std::uint32_t buf_appl2gul     = 1024 * 1024;
constexpr std::uint32_t buf_appl2appl    = 5 * 1024 * 1024;
constexpr std::uint32_t buf_appl2data    = 5 * 1024 * 1024;
constexpr std::uint32_t buf_appl2http    = 5 * 1024 * 1024;
constexpr std::uint32_t buf_appl2storage = 5 * 1024 * 1024;

#elif defined(U3_OS_ANDROID)

constexpr std::uint32_t buf_appl2gul     = 1 * buf_for_one_frame;
constexpr std::uint32_t buf_appl2appl    = 10 * 1024 * 1024;
constexpr std::uint32_t buf_appl2data    = 10 * 1024 * 1024;
constexpr std::uint32_t buf_appl2http    = 10 * 1024 * 1024;
constexpr std::uint32_t buf_appl2storage = 5 * 1024 * 1024;

#elif defined(U3_OS_MACX_DESKTOP)

constexpr std::uint32_t buf_appl2gul     = 2 * buf_for_one_frame;
constexpr std::uint32_t buf_appl2appl    = 20 * 1024 * 1024;
constexpr std::uint32_t buf_appl2data    = 20 * 1024 * 1024;
constexpr std::uint32_t buf_appl2http    = 20 * 1024 * 1024;
constexpr std::uint32_t buf_appl2storage = 10 * 1024 * 1024;

#else
#  error select OS
#endif
}   // namespace libs::link::consts::size
