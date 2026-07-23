#pragma once
/**
\file       vcodec-gen-proxy.hpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_proxy_libs
*/
// EAI-REFACT
// #include "mmedia/dlls/codecs/vcodec_gen/source/vcodec-gen-includes.hpp"
// #include "mmedia/dlls/codecs/vcodec_gen/source/vcodec-gen-syn.hpp"
#include "mmedia/dlls/codecs/vcodec_gen/source/funcs/dll-generic-codec-funcs.hpp"

namespace libs::proxy
{
auto get_create_codec_func (const std::string&) -> ::dlls::codecs::vcodec_gen::funcs::func_get_codec_type;
auto get_free_codec_func (const std::string&) -> ::dlls::codecs::vcodec_gen::funcs::func_free_codec_type;
auto get_info_codec_func (const std::string&) -> ::dlls::codecs::vcodec_gen::funcs::func_codec_info_type;
}   // namespace libs::proxy
