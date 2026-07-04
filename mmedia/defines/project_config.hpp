#pragma once
/**
\file		project_config.hpp.develop
\author		Erashov Anton erashov2026@proton.me
\date       19.10.2024
*/

namespace configure
{
inline constexpr const char* project_name     = "develop";
inline constexpr const char* git_hash         = "develop";
inline constexpr const char* start_build_time = "skip";
inline constexpr const char* compilers_info   = "OrangePi-Clang-_22_1_3-Clang-_22_1_3--aarch64-Release-none";

inline constexpr std::uint32_t project_ver_major = 0;
inline constexpr std::uint32_t project_ver_minor = 1;
}   // namespace configure
