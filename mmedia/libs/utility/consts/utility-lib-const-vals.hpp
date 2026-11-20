#pragma once
/**
\file       utility-lib-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace libs::utility::consts
{
inline constexpr std::string_view new_line { "\r" };          //<
inline constexpr std::uint32_t    uinvalid { 0xFFFFFFFFU };   //<
inline constexpr std::int32_t     iinvalid { -1 };            //<
}   // namespace libs::utility::consts
