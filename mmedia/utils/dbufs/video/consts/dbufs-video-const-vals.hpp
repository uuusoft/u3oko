#pragma once
/**
\file       dbufs-video-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2016
\project    u3_dbufs
*/

namespace utils::dbufs::video::consts
{
constexpr std::uint32_t min_width  = 160;         //< Минимальная ширина буфера в точках
constexpr std::uint32_t min_height = 120;         //< Минимальная высота буфера в точках
constexpr std::uint32_t max_width  = 16 * 1024;   //< Максимальная ширина буфера в точках
constexpr std::uint32_t max_height = 16 * 1024;   //< Максимальная высота буфере в точках
}   // namespace utils::dbufs::video::consts
