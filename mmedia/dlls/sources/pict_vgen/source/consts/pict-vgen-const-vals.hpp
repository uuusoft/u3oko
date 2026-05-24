#pragma once
/**
\file       pict-vgen-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       05.08.2024
\project    u3_pict_vgen
*/

namespace dlls::sources::pict_vgen::consts
{
constexpr std::int32_t max_count_cycle_store_image = 30;
}   // namespace dlls::sources::pict_vgen::consts

namespace dlls::sources::pict_vgen::consts::param_keys
{
extern const std::string picter_folder;
extern const std::string scroll_speed;
extern const std::string image2frame;
}   // namespace dlls::sources::pict_vgen::consts::param_keys
