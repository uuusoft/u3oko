#pragma once
/**
\file       frame-dims.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_codec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace codec_gen {
/**
  \brief
  */
struct FrameDims
{
  FrameDims ()
  {
    reset ();
  }

  ~FrameDims ()
  {}

  void
  reset ()
  {
    width_  = 0;
    height_ = 0;
    stride_ = 0;
    return;
  }

  bool
  check () const
  {
    UASSERT (width_ >= 0);
    UASSERT (height_ >= 0);
    UASSERT (width_ <= stride_);
    return width_ >= 0 && height_ >= 0 && width_ <= stride_;
  }

  short width_;       //< Ширина кадра.
  short height_;      //< Высота сохраняемых кадров
  short stride_;      //< Шаг в байтах кадра.
};
/**
\brief      Функция сброса поля в текстовый вид.
\param[in]  _val указатель на поле.
\return     текстовое описание поля.
*/
inline std::string
to_str (const FrameDims& _val)
{
  std::stringstream _str;
  _str << _val.width_ << "x" << _val.height_ << "x" << _val.stride_;
  return _str.str ();
}

}}}      // namespace dlls::codecs::codec_gen
