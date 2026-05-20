#pragma once
/**
\file       module-log-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_module_log
*/

namespace modules::uuu_log::appl::consts
{
extern const char* module_name;   //<

constexpr std::uint64_t g_size_tab              = 2;                                                                          //<
constexpr std::uint64_t g_max_count_tabs_date   = 15;                                                                         //<
constexpr std::uint64_t g_max_count_tabs_subsys = 6;                                                                          //<
constexpr std::uint64_t g_max_count_tabs_level  = 5;                                                                          //<
constexpr std::uint64_t g_max_count_tabs_info   = 90;                                                                         //<
constexpr std::uint64_t g_info_off_tabs         = g_max_count_tabs_subsys + g_max_count_tabs_date + g_max_count_tabs_level;   //<
}   // namespace modules::uuu_log::appl::consts
