#pragma once
/**
\file       convert-funcs.hpp
\date       29.08.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_vcodec_x264
*/

namespace dlls::codecs::vcodec_x264::impls::openh264::helpers
{
inline codec_gen::Frames
convert_frame_style (const EVideoFrameType& val)
{
  switch (val)
  {
  case videoFrameTypeIDR:
    return codec_gen::Frames::idrframe;
  case videoFrameTypeI:
    return codec_gen::Frames::iframe;
  case videoFrameTypeP:
    return codec_gen::Frames::pframe;
  case videoFrameTypeSkip:
    return codec_gen::Frames::unknown;
  case videoFrameTypeIPMixed:
    return codec_gen::Frames::unknown;
  case videoFrameTypeInvalid:
    U3_XLOG_ERROR ("invalid EVideoFrameType - videoFrameTypeInvalid");
    return codec_gen::Frames::unknown;
  }

  U3_XLOG_ERROR ("unknown val EVideoFrameType " + std::to_string (val));
  return codec_gen::Frames::unknown;
}
}   // namespace dlls::codecs::vcodec_x264::impls::openh264::helpers
