#pragma once
/**
\file       pict-vgen-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       05.08.2024
*/

namespace dlls::sources::pict_vgen::consts
{
inline constexpr std::int32_t max_count_cycle_store_image = 30;
}   // namespace dlls::sources::pict_vgen::consts

namespace dlls::sources::pict_vgen::consts::param_keys
{
inline constexpr std::string_view picter_folder = "dlls::sources::pict_vgen::picter_folder";
inline constexpr std::string_view scroll_speed  = "dlls::sources::pict_vgen::scroll_speed";
inline constexpr std::string_view image2frame   = "dlls::sources::pict_vgen::image2frame";
}   // namespace dlls::sources::pict_vgen::consts::param_keys
