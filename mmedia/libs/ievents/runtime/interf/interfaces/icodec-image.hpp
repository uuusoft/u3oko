#pragma once
/**
\file       icodec-image.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::interf::interfaces
{
class ICodecImage : public IBaseRuntimeInterf
{
  public:
  //  ext types
  using id_format_type = ::libs::helpers::utils::cuuid;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ICodecImage)

  virtual ~ICodecImage () = default;

  /// Функция возвращает индентификатор кодека, который поддерживается данной реализацией
  /// MPEG/x264/etc
  /// \return идентификатор формата из ::libs::helpers::uids::codecs
  const id_format_type&
  get_id_format () const
  {
    const id_format_type& ret = get_id_format_int ();
    U3_ASSERT (!ret.empty ());
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
  decode_image (const std::uint8_t* info, const std::int32_t size_info, ::utils::dbufs::IBuf::raw_ptr buf)
  {
    U3_ASSERT (info);
    U3_ASSERT (size_info > 0);
    U3_ASSERT (buf);
    decode_image_int (info, size_info, buf);
  }

  protected:
  ICodecImage () = default;

  private:
  //  ICodecImage interface
  virtual void                  code_image_int (::utils::dbufs::IBuf::raw_ptr buf)                                                           = 0;
  virtual void                  decode_image_int (const std::uint8_t* info, const std::int32_t size_info, ::utils::dbufs::IBuf::raw_ptr buf) = 0;
  virtual const id_format_type& get_id_format_int () const                                                                                   = 0;
  virtual void                  update_codec_property_int (const syn::VideoCodecProp::raw_ptr info)                                          = 0;
};
}   // namespace libs::ievents::runtime::interf::interfaces
