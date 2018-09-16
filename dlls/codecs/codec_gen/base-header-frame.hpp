#pragma once
/**
\file       base-header-frame.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.10.2016.
\copyright  www.uuusoft.com
\project    uuu_codec_gen
\brief      Описание формата кадра и информации связанной с сжатием.
*/

namespace dlls { namespace codecs { namespace codec_gen {
/**
\brief  Cтруктура, которая предворяет каждый сжатый кадр. 
        Ее можно детектировать без создания кодека.
*/
struct BaseHeaderFrame
{
  BaseHeaderFrame ()
  {
    reset ();
  }

  ~BaseHeaderFrame ()
  {}

  void
  reset ()
  {
    sinfo_.reset ();

    id_            = consts::id_frame;
    size_          = sizeof (BaseHeaderFrame);
    size_compress_ = 0;
    style_         = StyleFrame::unknown;

    std::fill (guid_ + 0, guid_ + COUNT_OF (guid_), UUU_ICAST_UCHAR (0));
    return;
  }

  bool
  check () const
  {
    if (consts::id_frame != id_)
      {
        XULOG_WARNING ("invalid id compress frame, " << id_ << "!=" << consts::id_frame);
        return false;
      }
    if (size_ < sizeof (BaseHeaderFrame))
      {
        XULOG_WARNING ("invalid size (too small) compress frame, " << size_ << "!=" << sizeof (BaseHeaderFrame));
        return false;
      }
    if (!sinfo_.check ())
      {
        XULOG_WARNING ("failed check compress frame");
        return false;
      }
    return true;
  }

  void
  set_guid_codec (const ::libs::helpers::utils::cuuid& _guid)
  {
    memcpy (guid_, _guid.get_vals ().data, sizeof (guid_));
    return;
  }

  unsigned long long id_;                 //< Идентификатор структуры, в принципе избыточен, константа. Добавлен для восстановления битых архивов.
  StyleFrame         style_;              //< Тип сжатого кадра (I/P/B/etc), лежит в узком диапазоне значений.
  FrameDims          sinfo_;              //< Геометрические размеры кадра, лежит в узком диапазоне значений.
  unsigned int       size_;               //< Общий размер заголовка сжатого кадра, лежит в узком диапазоне значений.
  unsigned int       size_compress_;      //< Размер сжатых данных, которые идут после данного заголовка.
  unsigned char      guid_[16];           //< Идентификатор кодека, переменный. Идет последним, чтобы точнее разбирать битые архивы.
};


inline void
dump (const BaseHeaderFrame& _val)
{
  XULOG_INFO ("   dump BaseHeaderFrame");
  XULOG_INFO ("       id=0x" << std::hex << _val.id_ << std::dec << ", style=" << to_str (_val.style_) << ", sinfo=" << to_str (_val.sinfo_) << ", size=" << _val.size_ << ", size_compress=" << _val.size_compress_ << ", guid=" << ::libs::helpers::uids::helpers::get_readable_name (::libs::helpers::utils::cuuid (_val.guid_)));
  return;
}

}}}      // namespace dlls::codecs::codec_gen
