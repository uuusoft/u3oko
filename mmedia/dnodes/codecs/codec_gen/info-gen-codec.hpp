#pragma once
/**
\file       info-gen-codec.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace dnodes::codecs::codec_gen
{
struct InfoGenCodec {
  // ext types
  U3_ADD_POINTERS_TO_SELF (InfoGenCodec)

  InfoGenCodec () = default;

  void
  check () const
  {
  }

  ::libs::icore::impl::base::obj::FilterInfo::raw_ptr codec_finfo_ = nullptr;   //<
};
}   // namespace dnodes::codecs::codec_gen
