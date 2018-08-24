#pragma once
/**
\file       header-iframe-hsl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_codec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace codec_gen {
//  syn
using ::libs::ievents::props::videos::generics::codec::VideoCodecFlatProp;
/**
  \brief  Cтруктура, которая предворяет каждый сжатый I кадр для HSL кодеков.
  */
struct HeaderIFrameHSL
{
  HeaderIFrameHSL ()
  {
    reset ();
  }

  ~HeaderIFrameHSL ()
  {}

  void
  reset ()
  {
    base_part_.reset ();

    cinfo_.reset ();

    base_part_.size_  = sizeof (HeaderIFrameHSL);
    base_part_.style_ = StyleFrame::iframe;

    std::fill (off_lhs_ + 0, off_lhs_ + COUNT_OF (off_lhs_), 0);
    std::fill (size_lhs_ + 0, size_lhs_ + COUNT_OF (size_lhs_), 0);
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
    if (base_part_.size_ < sizeof (HeaderIFrameHSL))
      {
        XULOG_WARNING ("size too small for ishl compress frame");
        return false;
      }
    return true;
  }

  BaseHeaderFrame    base_part_;        //< Базовая (плоская) часть.
  unsigned int       off_lhs_[3];       //< смещение независимо сжатых потоков HSL.
  unsigned int       size_lhs_[3];      //< размер независимо сжатых потоков HSL.
  VideoCodecFlatProp cinfo_;            //< установки кодека, используемые для данного кадра (и дальнешей последовательности кадров, зависящих от данного).
};

}}}      // namespace dlls::codecs::codec_gen
