#pragma once
/**
\file       -module-log-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace modules::mlog::appl::consts
{
inline constexpr std::string_view module_name { "u3_mlog" };                                                                      //<
inline constexpr std::uint64_t    g_size_tab { 2 };                                                                               //<
inline constexpr std::uint64_t    g_max_count_tabs_date { 15 };                                                                   //<
inline constexpr std::uint64_t    g_max_count_tabs_subsys { 6 };                                                                  //<
inline constexpr std::uint64_t    g_max_count_tabs_level { 5 };                                                                   //<
inline constexpr std::uint64_t    g_max_count_tabs_info { 90 };                                                                   //<
inline constexpr std::uint64_t    g_info_off_tabs { g_max_count_tabs_subsys + g_max_count_tabs_date + g_max_count_tabs_level };   //<
}   // namespace modules::mlog::appl::consts
