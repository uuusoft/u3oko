#pragma once
/**
\file       invert_rows.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_dbufs
*/

namespace utils::dbufs::video::helpers
{
inline void
invert_rows (IVideoBuf::raw_ptr buf)
{
  U3_CHECK (buf, "empty buf for fill");
  if (!buf->get_buf () || !(*buf)[MemVars::size_buf] || buf->get_flag (BufFlags::empty))
  {
    return;
  }

  const auto _height = buf->get_dim_var (Dims::height);
  const auto _width  = buf->get_dim_var (Dims::width);

  for (std::int32_t indxy1 = 0, indxy2 = _height - 1; indxy1 < indxy2; ++indxy1, --indxy2)
  {
    auto _line1 = get_line_data_as< std::int16_t* > (buf, indxy1);
    auto _line2 = get_line_data_as< std::int16_t* > (buf, indxy2);

    for (std::uint32_t indxx = 0; indxx < _width; ++indxx)
    {
      std::swap (_line1[indxx], _line2[indxx]);
    }
  }
}
}   // namespace utils::dbufs::video::helpers
