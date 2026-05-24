#pragma once
/**
\file       v4l2-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.02.2026
\project    u3_v4l2_vgen
*/

namespace dlls::sources::v4l2_vgen::consts
{
constexpr std::size_t max_check_device_count = 4;                               //<
constexpr std::chrono::milliseconds ms_timeout_recreate_device { 60 * 1000 };   //< 60 sec
extern const std::string            dev_path;                                   //<
}   // namespace dlls::sources::v4l2_vgen::consts
