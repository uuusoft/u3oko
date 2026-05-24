#pragma once
/**
\file       ibase-h264-impl.hpp
\date       06.07.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_x264
*/

namespace dlls::codecs::vcodec_x264::impls
{
struct EncodeFrameState final {
  explicit EncodeFrameState (
    syn::IVideoBuf::raw_ptr sbuf,
    syn::IVideoBuf::raw_ptr dbuf,
    bool                    nocolor) :
    sbuf_ (sbuf),
    nocolor_ (nocolor),
    dbuf_ (dbuf)
  {
  }

  syn::IVideoBuf::raw_ptr sbuf_;      //<
  syn::IVideoBuf::raw_ptr dbuf_;      //<
  bool                    nocolor_;   //<
};

class IBaseH264Impl
{
  public:
  // ext types
  using frame_formats_type = std::unordered_set< ::libs::helpers::uids::minor::id_val >;

  virtual ~IBaseH264Impl ()
  {
  }

  void
  create_coder (
    const syn::VideoCodecProp& cinfo,
    const syn::AllocBufInfo&   coder_frame_info)
  {
    create_coder_int (cinfo, coder_frame_info);
  }

  void
  destroy_coder ()
  {
    destroy_coder_int ();
  }

  void
  create_decoder ()
  {
    create_decoder_int ();
  }

  void
  destroy_decoder ()
  {
    destroy_decoder_int ();
  }

  const frame_formats_type&
  get_support_frame_format (const syn::CodecModes& codec_mode) const
  {
    return get_support_frame_format_int (codec_mode);
  }

  bool
  compress_frame (const syn::VideoCodecProp& cinfo, EncodeFrameState& state)
  {
    return compress_frame_int (cinfo, state);
  }

  bool
  decompress_frame (
    const syn::HeaderIFrame*           head,
    const ::libs::optim::io::ProxyBuf& src,
    const std::int32_t                 src_size,
    const syn::IVideoBuf::raw_ptr      idst,
    std::uint8_t**                     dst,
    std::uint32_t&                     dst_stride,
    std::uint32_t&                     dst_width,
    std::uint32_t&                     dst_height)
  {
    return decompress_frame_int (head, src, src_size, idst, dst, dst_stride, dst_width, dst_height);
  }

  protected:
  IBaseH264Impl ()
  {
  }

  private:
  virtual bool compress_frame_int (const syn::VideoCodecProp&, EncodeFrameState&)                                                                                                                                     = 0;
  virtual bool decompress_frame_int (const syn::HeaderIFrame*, const ::libs::optim::io::ProxyBuf&, const std::int32_t, const syn::IVideoBuf::raw_ptr, std::uint8_t**, std::uint32_t&, std::uint32_t&, std::uint32_t&) = 0;
  virtual void create_coder_int (const syn::VideoCodecProp&, const syn::AllocBufInfo&)                                                                                                                                = 0;
  virtual void destroy_coder_int ()                                                                                                                                                                                   = 0;
  virtual void create_decoder_int ()                                                                                                                                                                                  = 0;
  virtual void destroy_decoder_int ()                                                                                                                                                                                 = 0;

  virtual const frame_formats_type& get_support_frame_format_int (const syn::CodecModes& codec_mode) const = 0;
};
}   // namespace dlls::codecs::vcodec_x264::impls
