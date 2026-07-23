#pragma once
/**
\file       codec-funcs-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_codec_funcs
*/

namespace dlls::codecs::consts
{
inline constexpr std::uint32_t dim_elements_macroblock   = 8;    //<
inline constexpr std::uint32_t count_elements_macroblock = 64;   //<
inline constexpr std::uint32_t off_bits                  = 3;    //<
inline constexpr std::uint32_t max_size_set              = 30;   //< define max set for adaptive insert key frame
}   // namespace dlls::codecs::consts
