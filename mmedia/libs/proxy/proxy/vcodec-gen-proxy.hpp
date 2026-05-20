#pragma once
/**
\file       vcodec-gen-proxy.hpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    uuu_proxy
*/
// EAI-REFACT
#include "mmedia/dlls/codecs/vcodec_gen/source/funcs/dll-generic-codec-funcs.hpp"

namespace libs::proxy
{
::dlls::codecs::vcodec_gen::funcs::func_get_codec_type  get_create_codec_func (const std::string& plib_id);
::dlls::codecs::vcodec_gen::funcs::func_free_codec_type get_free_codec_func (const std::string& plib_id);
::dlls::codecs::vcodec_gen::funcs::func_codec_info_type get_info_codec_func (const std::string& plib_id);
}   // namespace libs::proxy
