#pragma once
/**
\file       codec-funcs-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_codec_funcs
*/
#ifndef U3_CAST_CODECS
#  define U3_CAST_CODECS reinterpret_cast
#endif

#ifndef MPTR
#  define MPTR qword ptr
#endif

namespace dlls::codecs::consts
{
constexpr std::uint32_t dim_elements_macroblock   = 8;    //<
constexpr std::uint32_t count_elements_macroblock = 64;   //<
constexpr std::uint32_t off_bits                  = 3;    //<
constexpr std::uint32_t max_size_set              = 30;   //< define max set for adaptive insert key frame
}   // namespace dlls::codecs::consts
