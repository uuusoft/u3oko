#pragma once
/**
\file       open-h264-impl.hpp
\date       06.07.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_x264
*/
class ISVCEncoder;
class ISVCDecoder;

namespace dlls::codecs::vcodec_x264::impls::openh264
{
class OpenH264Impl final : public ::dlls::codecs::vcodec_x264::impls::IBaseH264Impl
{
  public:
  OpenH264Impl ();
  virtual ~OpenH264Impl ();

  private:
  virtual bool compress_frame_int (const syn::VideoCodecProp&, EncodeFrameState&) override;
  virtual bool decompress_frame_int (const syn::HeaderIFrame*, const ::libs::optim::io::ProxyBuf&, const std::int32_t, const syn::IVideoBuf::raw_ptr, std::uint8_t**, std::uint32_t& dst_stride, std::uint32_t&, std::uint32_t&) override;
  virtual void create_coder_int (const syn::VideoCodecProp&, const syn::AllocBufInfo&) override;
  virtual void destroy_coder_int () override;
  virtual void create_decoder_int () override;
  virtual void destroy_decoder_int () override;

  virtual const IBaseH264Impl::frame_formats_type& get_support_frame_format_int (const syn::CodecModes& codec_mode) const override;

  ISVCEncoder* coder_;     //< Implementing of coder
  ISVCDecoder* decoder_;   //< Implementing of decoder
};
}   // namespace dlls::codecs::vcodec_x264::impls::openh264
