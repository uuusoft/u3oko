#pragma once
/**
\file       header-iframe.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_codec_gen
*/

namespace dlls::codecs::codec_gen
{
/// Cтруктура, которая предворяет каждый сжатый I кадр для кодеков
struct HeaderIFrame final {
  HeaderIFrame ()
  {
    reset ();
  }

  ~HeaderIFrame () = default;

  void
  reset ()
  {
    base_part_.reset ();
    cinfo_.reset ();

    base_part_.size_  = sizeof (HeaderIFrame);
    base_part_.style_ = Frames::iframe;
    coff_             = 0;
    csize_            = 0;
  }

  bool
  check () const
  {
    if (!base_part_.check ())
    {
      U3_XLOG_WARN ("check base part compress frame");
      return false;
    }

    if (base_part_.size_ < sizeof (HeaderIFrame))
    {
      U3_XLOG_WARN ("size too small for i compress frame");
      return false;
    }
    return true;
  }

  BaseHeaderFrame         base_part_;   //< Базовая (плоская) часть
  std::uint32_t           coff_  = 0;   //< Cмещение независимо сжатого потока
  std::uint32_t           csize_ = 0;   //< Размер независимо сжатого потока
  syn::VideoCodecFlatProp cinfo_;       //< Установки кодека, используемые для данного кадра (и дальнешей последовательности кадров, зависящих от данного)
};

/// Функция сброса поля в текстовый вид
/// \param[in]  val указатель на поле
/// \return текстовое описание поля
inline void
dump (const HeaderIFrame& val)
{
  dump (val.base_part_);
}
}   // namespace dlls::codecs::codec_gen
