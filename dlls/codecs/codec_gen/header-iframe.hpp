//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       header-iframe.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_codec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace codec_gen {
//  syn
using ::libs::ievents::props::videos::generics::codec::VideoCodecFlatProp;
/**
\brief  Cтруктура, которая предворяет каждый сжатый I кадр для кодеков.
*/
struct HeaderIFrame
{
  HeaderIFrame ()
  {
    reset ();
  }

  ~HeaderIFrame ()
  {}

  void
  reset ()
  {
    base_part_.reset ();
    cinfo_.reset ();
    base_part_.size_  = sizeof (HeaderIFrame);
    base_part_.style_ = StyleFrame::iframe;
    coff_             = 0;
    csize_            = 0;
    return;
  }

  bool
  check () const
  {
    if (!base_part_.check ())
      {
        XULOG_WARNING ("failed check base part compress frame");
        return false;
      }

    if (base_part_.size_ < sizeof (HeaderIFrame))
      {
        XULOG_WARNING ("size too small for i compress frame");
        return false;
      }
    return true;
  }

  BaseHeaderFrame    base_part_;      //< Базовая (плоская) часть.
  unsigned int       coff_;           //< Cмещение независимо сжатого потока.
  unsigned int       csize_;          //< Размер независимо сжатого потока.
  VideoCodecFlatProp cinfo_;          //< Установки кодека, используемые для данного кадра (и дальнешей последовательности кадров, зависящих от данного).
};
/**
\brief      Функция сброса поля в текстовый вид.
\param[in]  _val указатель на поле.
\return     текстовое описание поля.
*/
inline void
dump (const HeaderIFrame& _val)
{
  XULOG_INFO ("dump HeaderIFrame");
  dump (_val.base_part_);
  XULOG_INFO ("   coff=" << _val.coff_ << ", csize=" << _val.csize_);
  return;
}

}}}      // namespace dlls::codecs::codec_gen
