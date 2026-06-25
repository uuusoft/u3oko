#pragma once
/**
\file       gen-vgen-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_gen_vgen
*/

namespace dlls::sources::gen_vgen::consts
{
#if defined(U3_OS_WIN32_DESKTOP) || defined(U3_OS_GNU_LINUX) || defined(U3_OS_MACX_DESKTOP)
constexpr std::chrono::milliseconds ms_delay_skip_cycle { 1 };
#elif defined(U3_OS_ANDROID)
constexpr std::chrono::milliseconds ms_delay_skip_cycle { 1 };
#elif defined(U3_OS_RASPBERRY)
constexpr std::chrono::milliseconds ms_delay_skip_cycle { 1 };
#elif defined(U3_OS_ORANGE_PI)
constexpr std::chrono::milliseconds ms_delay_skip_cycle { 1 };
#else
#  error select OS
#endif

constexpr std::chrono::milliseconds ms_wait_capture_device { 5 * 1000 };               //< 5sec
constexpr std::chrono::milliseconds ms_delay_skip_cycle_before_start_device { 500 };   //< 500ms
}   // namespace dlls::sources::gen_vgen::consts
