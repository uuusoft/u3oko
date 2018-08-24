#pragma once
//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       icodec-image.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
*/

namespace libs { namespace ievents { namespace runtime { namespace interf {
//  syn
using ::libs::ievents::props::videos::generics::codec::VideoCodecProp;
using ::utils::dbuffs::IBuff;
/**
  \brief  ��������� ���������� (������ ����� ����������) ������������� �����������.
  */
class ICodecImage
{
  public:
  //  ext types
  using id_format_type = ::libs::helpers::utils::cuuid;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ICodecImage);

  virtual ~ICodecImage ()
  {}
  /**
  \brief  Функция возвращает индентификатор кодека, который поддерживается данной реализацией. MPEG/x264/etc.
  \return идентификатор формата из ::libs::helpers::uids::codecs
  */
  const id_format_type&
  get_id_format () const
  {
    const id_format_type& _ret = get_id_format_int ();
    UASSERT (!_ret.empty ());
    return _ret;
  }

  void
  update_codec_property (const VideoCodecProp::raw_ptr _info)
  {
    update_codec_property_int (_info);
    return;
  }

  void
  code_image (IBuff::raw_ptr _buff)
  {
    return code_image_int (_buff);
  }

  void
  decode_image (const unsigned char* _info, const int _size_info, IBuff::raw_ptr _buff)
  {
    UASSERT (_info);
    UASSERT (_size_info > 0);
    UASSERT (_buff);
    return decode_image_int (_info, _size_info, _buff);
  }


  protected:
  ICodecImage ()
  {}


  private:
  //  ICodecImage interface
  virtual void                  code_image_int (IBuff::raw_ptr _buff)                                                    = 0;
  virtual void                  decode_image_int (const unsigned char* _info, const int size_info, IBuff::raw_ptr _buff) = 0;
  virtual const id_format_type& get_id_format_int () const                                                               = 0;
  virtual void                  update_codec_property_int (const VideoCodecProp::raw_ptr _info)                          = 0;
};

}}}}      // namespace libs::ievents::runtime::interf
