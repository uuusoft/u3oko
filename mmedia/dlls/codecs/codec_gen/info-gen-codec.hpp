#pragma once
/**
\file       info-gen-codec.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_codec_gen
*/

namespace dlls::codecs::codec_gen
{
struct InfoGenCodec {
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (InfoGenCodec)

  InfoGenCodec ()
  {
  }

  void
  check () const
  {
  }

  ::libs::icore::impl::var1::obj::FilterInfo::raw_ptr codec_finfo_ = nullptr;   //<
};
}   // namespace dlls::codecs::codec_gen
