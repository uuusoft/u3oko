#pragma once
/**
\file       base-header-frame.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.10.2016
\project    u3_codec_gen
*/

namespace dlls::codecs::codec_gen
{
/// Cтруктура, которая предворяет каждый сжатый кадр
/// Ее можно детектировать без создания кодека.
struct BaseHeaderFrame final {
  BaseHeaderFrame ()
  {
    reset ();
  }

  ~BaseHeaderFrame ()
  {
  }

  void
  reset ()
  {
    sinfo_.reset ();

    id_            = consts::id_frame;
    size_          = sizeof (BaseHeaderFrame);
    size_compress_ = 0;
    style_         = Frames::unknown;
    guid_          = libs::helpers::uids::minor::id_val::unknown;
  }

  bool
  check () const
  {
    if (consts::id_frame != id_)
    {
      U3_XLOG_WARN ("invalid id compress frame" + VTOLOG (id_) + "!=" + VTOLOG (consts::id_frame));
      return false;
    }
    if (size_ < sizeof (BaseHeaderFrame))
    {
      U3_XLOG_WARN ("invalid size (too small) compress frame" + VTOLOG (size_) + "!=" + VTOLOG (sizeof (BaseHeaderFrame)));
      return false;
    }
    if (!sinfo_.check ())
    {
      U3_XLOG_WARN ("check compress frame");
      return false;
    }
    return true;
  }

  std::uint64_t                      id_;              //< Идентификатор структуры, в принципе избыточен, константа. Добавлен для восстановления битых архивов
  Frames                             style_;           //< Тип сжатого кадра (I/P/B/etc), лежит в узком диапазоне значений
  FrameDims                          sinfo_;           //< Геометрические размеры кадра, лежит в узком диапазоне значений
  std::uint32_t                      size_;            //< Общий размер заголовка сжатого кадра, лежит в узком диапазоне значений
  std::uint32_t                      size_compress_;   //< Размер сжатых данных, которые идут после данного заголовка
  libs::helpers::uids::minor::id_val guid_;            //< Идентификатор кодека, переменный. Идет последним, чтобы точнее разбирать битые архивы
};

inline void
dump (const BaseHeaderFrame& val)
{
}
}   // namespace dlls::codecs::codec_gen
