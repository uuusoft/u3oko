#pragma once
/**
\file       copy2dlib-helper-func.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_detect_face
*/
#ifndef U3_SKIP_DLIB

namespace dlls::detectors::detect_face::helpers
{
template< typename TPixel >
void
copy2dlib (syn::IVideoBuf::raw_ptr psrc, dlib::array2d< TPixel >& img)
{
  const std::size_t width  = psrc->get_dim_var (utils::dbufs::video::Dims::width);
  const std::size_t height = psrc->get_dim_var (utils::dbufs::video::Dims::height);

  img.set_size (height, width);

  for (std::size_t indxy = 0; indxy < height; ++indxy)
  {
    auto row  = img[indxy];
    auto srow = ::utils::dbufs::video::helpers::get_line_const_data_as< const std::int16_t* > (psrc, indxy);

    for (std::size_t indxx = 0; indxx < width; ++indxx)
    {
      auto px = srow[indxx];

      px         = px < 0 ? 0 : (px > 255 ? 255 : px);
      row[indxx] = U3_CAST_STATIC< TPixel > (px);
    }
  }
}
}   // namespace dlls::detectors::detect_face::helpers

#endif
