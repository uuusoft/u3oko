#pragma once
/**
\file       mems-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       17.04.2022
\project    u3_mems
*/

namespace utils::mems::impl::consts
{
inline constexpr std::uint64_t min_size_block                = 32 * 1024;   //<
inline constexpr std::uint64_t max_count_block               = 16 * 1024;   //<
inline constexpr std::uint64_t default_reserved_count_blocks = 2 * 1024;    //<
}   // namespace utils::mems::impl::consts
