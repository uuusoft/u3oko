#pragma once
/**
\file       header-iframe-hsl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_codec_gen
*/

namespace dlls::codecs::codec_gen
{
/// Cтруктура, которая предворяет каждый сжатый I кадр для HSL кодеков
struct HeaderIFrameHSL final {
  HeaderIFrameHSL ()
  {
    reset ();
  }

  ~HeaderIFrameHSL () = default;

  void
  reset ()
  {
    base_part_.reset ();

    cinfo_.reset ();

    base_part_.size_  = sizeof (HeaderIFrameHSL);
    base_part_.style_ = Frames::iframe;

    std::fill (off_lhs_ + 0, off_lhs_ + std::size (off_lhs_), 0);
    std::fill (size_lhs_ + 0, size_lhs_ + std::size (size_lhs_), 0);
  }

  bool
  check () const
  {
    if (!base_part_.check ())
    {
      U3_XLOG_WARN ("check base part compress frame");
      return false;
    }
    if (base_part_.size_ < sizeof (HeaderIFrameHSL))
    {
      U3_XLOG_WARN ("size too small for ishl compress frame");
      return false;
    }
    return true;
  }

  BaseHeaderFrame         base_part_;     //< Базовая (плоская) часть
  std::uint32_t           off_lhs_[3];    //< смещение независимо сжатых потоков HSL
  std::uint32_t           size_lhs_[3];   //< размер независимо сжатых потоков HSL
  syn::VideoCodecFlatProp cinfo_;         //< установки кодека, используемые для данного кадра (и дальнешей последовательности кадров, зависящих от данного)
};
}   // namespace dlls::codecs::codec_gen
