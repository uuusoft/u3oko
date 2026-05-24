#pragma once
/**
\file       factory-h264-impl.hpp
\date       06.07.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_x264
*/

namespace dlls::codecs::vcodec_x264::impls
{
class FactoryH264Impl final
{
  public:
  static auto
  get_impl ()
  {
    return std::make_unique< dlls::codecs::vcodec_x264::impls::openh264::OpenH264Impl > ();
  }
};
}   // namespace dlls::codecs::vcodec_x264::impls
