#pragma once
/**
\file       mem-funcs-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       17.04.2022
\project    u3_mem_funcs
*/

namespace utils::mem_funcs::impl::consts
{
constexpr std::uint64_t min_size_block                = 32 * 1024;   //<
constexpr std::uint64_t max_count_block               = 16 * 1024;   //<
constexpr std::uint64_t default_reserved_count_blocks = 2 * 1024;    //<
}   // namespace utils::mem_funcs::impl::consts
