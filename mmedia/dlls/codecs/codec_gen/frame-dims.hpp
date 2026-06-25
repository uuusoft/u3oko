#pragma once
/**
\file       frame-dims.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_codec_gen
*/

namespace dlls::codecs::codec_gen
{
struct FrameDims final {
  ~FrameDims () = default;

  void
  reset ()
  {
    width_  = 0;
    height_ = 0;
    stride_ = 0;
  }

  bool
  check () const
  {
    U3_ASSERT (width_ >= 0);
    U3_ASSERT (height_ >= 0);
    U3_ASSERT (width_ <= stride_);
    return width_ >= 0 && height_ >= 0 && width_ <= stride_;
  }

  std::int16_t width_  = 0;   //< Ширина кадра
  std::int16_t height_ = 0;   //< Высота сохраняемых кадров
  std::int16_t stride_ = 0;   //< Шаг в байтах кадра
};

/// Функция сброса поля в текстовый вид
/// \param[in]  val указатель на поле
/// \return текстовое описание поля
inline std::string
to_string (const FrameDims& val)
{
  std::stringstream str;
  str << val.width_ << "x" << val.height_ << "x" << val.stride_;
  return str.str ();
}
}   // namespace dlls::codecs::codec_gen
