#pragma once
/**
\file       load-codec-from-file-funcs.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
*/

namespace dnodes::codecs::vcodec_gen::helpers
{
auto load_codec_from_file (
  bool               decorate_name,
  const std::string& file_name,
  CodecImplInfo&     info) -> void;
}   // namespace dnodes::codecs::vcodec_gen::helpers
