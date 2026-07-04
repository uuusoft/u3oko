#pragma once
/**
\file       swap-buf-data-by-rows-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_dbufs
*/

namespace utils::dbufs::video::helpers
{
inline void
swap_buf_data_by_rows (IVideoBuf::raw_ptr buf)
{
  U3_CHECK (buf, "try fill null buf");
  if (!buf->get_buf () || !(*buf)[MemVars::size_buf] || buf->get_flag (BufFlags::empty))
  {
    return;
  }

  const auto height = buf->get_dim_var (Dims::height);
  const auto width  = buf->get_dim_var (Dims::width);

  for (std::int32_t top = 0, bottom = height - 1; top < bottom; ++top, --bottom)
  {
    auto topline    = get_line_data_as< std::int16_t* > (buf, top);
    auto bottomline = get_line_data_as< std::int16_t* > (buf, bottom);
    for (std::uint32_t pix = 0; pix < width; ++pix)
    {
      std::swap (topline[pix], bottomline[pix]);
    }
  }
}
}   // namespace utils::dbufs::video::helpers
