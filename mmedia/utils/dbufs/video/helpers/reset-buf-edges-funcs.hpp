#pragma once
/**
\file       reset-buf-edges-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_dbufs
*/

namespace utils::dbufs::video::helpers
{
/// Вспомогательная функция сброса-отчистки "краев" изображения в 0
/// \param[in]  buf буфер, края которого сбрасываются
inline void
reset_edges (IVideoBuf::raw_ptr buf)
{
  U3_CHECK (buf, "empty buf for reset edges");

  if (buf->get_flag (::utils::dbufs::BufFlags::empty))
  {
    ::libs::utility::mem::set_buf< std::uint8_t > (buf->get_buf (), 0, (*buf)[MemVars::size_buf]);
    return;
  }

  const auto buf_format = buf->get_format ();
  if (!::libs::utility::uids::helpers::is_raw_format (buf_format))
  {
    U3_XLOG_WARN ("try reset compressed format");
    return;
  }

  const auto off_leak = (*buf)[MemVars::offset_data] + (*buf)[MemVars::size_data];
  U3_CHECK ((*buf)[utils::dbufs::MemVars::size_buf] >= off_leak, "off leak negative");

  //  заполняем начало.
  ::libs::utility::mem::set_buf< std::uint8_t > (buf->get_buf (), 0, (*buf)[MemVars::offset_data]);
  //  заполняем конец.
  ::libs::utility::mem::set_buf< std::uint8_t > (buf->get_buf () + off_leak, 0, (*buf)[MemVars::size_buf] - off_leak);

  const auto _height     = buf->get_dim_var (Dims::height);
  const auto _data_width = buf->get_dim_var (Dims::width) * ::libs::utility::uids::helpers::get_count_bytes_from_format (buf_format);
  const auto _leak_width = buf->get_dim_var (Dims::stride) - _data_width;

  //  заполняем каждый остаток строки.
  for (std::remove_cv< decltype (_height) >::type indxy = 0; indxy < _height; ++indxy)
  {
    std::uint8_t* _str_data = get_line_data_as< std::uint8_t* > (buf, indxy) + _data_width;
    ::libs::utility::mem::set_buf< std::uint8_t > (_str_data, 0, _leak_width);
  }
}
}   // namespace utils::dbufs::video::helpers
