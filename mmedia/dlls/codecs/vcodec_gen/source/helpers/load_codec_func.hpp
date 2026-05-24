#pragma once
/**
\file       load_codec_func.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_gen
*/

namespace dlls::codecs::vcodec_gen::helpers
{
void
load_codec_from_file (
  bool               decorate_name,
  const std::string& file_name,
  CodecImplInfo&     info);
}   // namespace dlls::codecs::vcodec_gen::helpers
