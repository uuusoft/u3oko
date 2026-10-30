#pragma once
/**
\file       icodec-image.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
*/

namespace libs::events_base::runtime::interf::interfaces
{
class ICodecImage : public IBaseRuntimeInterf
{
  public:
  //  ext types
  using id_format_type = ::libs::utility::utils::cuuid;

  U3_ADD_POINTERS_TO_SELF (ICodecImage)

  virtual ~ICodecImage () = default;

  /// Функция возвращает индентификатор кодека, который поддерживается данной реализацией MPEG/x264/etc
  /// \return идентификатор формата из ::libs::utility::uids::codecs
  const id_format_type&
  get_id_format () const
  {
    const id_format_type& ret = get_id_format_int ();
    ::libs::utility::checks::throw_ifn (!ret.empty ());
    return ret;
  }

  void
  update_codec_property (const syn::VideoCodecProp::raw_ptr info)
  {
    update_codec_property_int (info);
  }

  void
  code_image (::utils::dbufs::IBuf::raw_ptr buf)
  {
    code_image_int (buf);
  }

  void
  decode_image (const std::uint8_t* info, const std::int32_t size_info, syn::IBuf::raw_ptr buf)
  {
    ::libs::utility::checks::throw_ifn (info);
    ::libs::utility::checks::throw_ifn (size_info > 0);
    ::libs::utility::checks::throw_ifn ((bool) buf);
    decode_image_int (info, size_info, buf);
  }

  protected:
  ICodecImage () = default;

  private:
  //  ICodecImage interface
  virtual auto code_image_int (syn::IBuf::raw_ptr) -> void                                            = 0;
  virtual auto decode_image_int (const std::uint8_t*, const std::int32_t, syn::IBuf::raw_ptr) -> void = 0;
  virtual auto get_id_format_int () const -> const id_format_type&                                    = 0;
  virtual auto update_codec_property_int (const syn::VideoCodecProp::raw_ptr) -> void                 = 0;
};
}   // namespace libs::events_base::runtime::interf::interfaces
