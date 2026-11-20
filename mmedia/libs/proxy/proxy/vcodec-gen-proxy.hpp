#pragma once
/**
\file       vcodec-gen-proxy.hpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me
*/
// EAI-REFACT
#include "mmedia/dlls/codecs/vcodec_gen/source/funcs/dll-generic-codec-funcs.hpp"

namespace libs::proxy::syn
{
namespace funcs = ::dlls::codecs::vcodec_gen::funcs;
}   // namespace libs::proxy::syn

namespace libs::proxy
{
auto get_create_codec_func (const std::string&) -> syn::funcs::func_get_codec_type;
auto get_free_codec_func (const std::string&) -> syn::funcs::func_free_codec_type;
auto get_info_codec_func (const std::string&) -> syn::funcs::func_codec_info_type;
}   // namespace libs::proxy
