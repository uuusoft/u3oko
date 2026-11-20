#pragma once
/**
\file       vcodec-gen-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace dlls::codecs::vcodec_gen::consts
{
inline constexpr std::string_view func_name_create_codec = "create_codec";     //<
inline constexpr std::string_view func_name_delete_codec = "delete_codec";     //<
inline constexpr std::string_view func_name_get_info     = "get_codec_info";   //<
inline constexpr std::int32_t     max_off_times          = 16;                 //< offset const for calculate times
}   // namespace dlls::codecs::vcodec_gen::consts
