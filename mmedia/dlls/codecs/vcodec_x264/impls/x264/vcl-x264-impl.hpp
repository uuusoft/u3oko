#pragma once
/**
\file       vcl-x264-impl.hpp
\date       07.07.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_x264
*/

#if 0
namespace dlls::codecs::vcodec_x264::impls::x264
{
class VclX264Impl final : public ::dlls::codecs::vcodec_x264::impls::IBaseH264Impl
{
  public:
  VclX264Impl ();
  virtual ~VclX264Impl ();

  private:
  virtual bool compress_frame_int (const syn::VideoCodecProp& cinfo, EncodeFrameState& state) override;
  virtual bool decompress_frame_int (const syn::HeaderIFrame* head, const ::libs::optim::io::ProxyBuf& src, const std::int32_t src_size, const ::utils::dbufs::video::IVideoBuf::raw_ptr idst, std::uint8_t** dst, std::uint32_t& dst_stride, std::uint32_t& dst_width, std::uint32_t& dst_height) override;
  virtual void create_coder_int (const syn::VideoCodecProp& cinfo, const syn::AllocBufInfo& coder_frame_info) override;
  virtual void destroy_coder_int () override;
  virtual void create_decoder_int () override;
  virtual void destroy_decoder_int () override;

  virtual const IBaseH264Impl::frame_formats_type& get_support_frame_format_int (const syn::CodecModes& codec_mode) const override;

  // ISVCEncoder* coder_;     //< Implementing of coder
  // ISVCDecoder* decoder_;   //< Implementing of decoder
};
}   // namespace dlls::codecs::vcodec_x264::impls::x264
#endif
