#pragma once
/**
\file       vcodec-gen-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_vcodec_gen
*/

namespace dlls::codecs::vcodec_gen::consts
{
extern const std::string func_name_create_codec;   //<
extern const std::string func_name_delete_codec;   //<
extern const std::string func_name_get_info;       //<

inline constexpr std::int32_t max_off_times = 16;   //< offset const for calculate times
}   // namespace dlls::codecs::vcodec_gen::consts
