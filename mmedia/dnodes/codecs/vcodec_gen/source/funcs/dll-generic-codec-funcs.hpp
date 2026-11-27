#pragma once
/**
\file       dll-generic-codec-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace dnodes::codecs::codec_gen
{
class CodecGeneric;
}   // namespace dnodes::codecs::codec_gen

namespace dnodes::codecs::vcodec_gen::funcs
{
using get_codec_info_func_type = void (::libs::utility::uids::minor::id_val guids[4]);
using func_codec_info_type     = std::function< get_codec_info_func_type >;

using get_codec_func_type = void (::dnodes::codecs::codec_gen::CodecGeneric** pobj);
using func_get_codec_type = std::function< get_codec_func_type >;

using free_codec_func_type = void (::dnodes::codecs::codec_gen::CodecGeneric* obj);
using func_free_codec_type = std::function< free_codec_func_type >;
}   // namespace dnodes::codecs::vcodec_gen::funcs
