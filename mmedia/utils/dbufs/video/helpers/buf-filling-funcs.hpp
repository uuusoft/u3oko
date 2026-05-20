#pragma once
/**
\file       buf-filling-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_dbufs
*/

namespace utils::dbufs::video::helpers
{
inline void
fill (IVideoBuf::raw_ptr buf, std::uint8_t _val)
{
  U3_CHECK (buf, "empty buf for fill");
  if (!buf->get_buf () || !(*buf)[MemVars::size_buf])
  {
    return;
  }

  memset (buf->get_buf (), _val, (*buf)[MemVars::size_buf]);
}


template< typename TPx >
void
fill (IVideoBuf::raw_ptr                                                                buf,
      const std::function< void (std::uint32_t indxx, std::uint32_t indxy, TPx& val) >& func)
{
  U3_CHECK (buf, "empty buf for fill");
  if (!buf->get_buf () || 0 == (*buf)[MemVars::size_buf] || buf->get_flag (BufFlags::empty))
  {
    return;
  }

  const auto _height = buf->get_dim_var (Dims::height);
  const auto _width  = buf->get_dim_var (Dims::width);

  for (std::uint32_t indxy = 0; indxy < _height; ++indxy)
  {
    auto _line = get_line_data_as< TPx* > (buf, indxy);
    for (std::uint32_t indxx = 0; indxx < _width; ++indxx)
    {
      func (indxx, indxy, _line[indxx]);
    }
  }
}


template< typename TPx >
void
fill_buf (IVideoBuf::raw_ptr buf, const std::function< void (std::uint32_t indx, TPx& val) >& func)
{
  U3_CHECK (buf, "empty buf for fill");
  const auto size    = (*buf)[MemVars::size_data];
  auto       _begbuf = get_buf_as< TPx* > (buf);

  if (!_begbuf || 0 == size || buf->get_flag (BufFlags::null))
  {
    return;
  }

  for (std::uint32_t _indx = 0; _indx < size; ++_indx)
  {
    func (_indx, _begbuf[_indx]);
  }
}


inline void
raw_copy (
  const std::uint8_t* _rbuf,
  std::uint32_t       size,
  IVideoBuf::raw_ptr  buf,
  std::uint32_t       off_dest = 0)
{
  U3_CHECK (buf, "empty buf for raw copy");
  U3_CHECK (_rbuf, "empty source for raw copy");
  U3_CHECK (size, "null for raw copy");
  U3_CHECK ((*buf)[MemVars::size_buf] >= size + off_dest, "size too small");

  buf->set_mem_var (MemVars::size_data, size);
  buf->set_mem_var (MemVars::offset_data, 0);

  ::libs::helpers::mem::u3copy (_rbuf, buf->get_buf () + off_dest, size);
}


inline void
copy_video_buf2vector (::utils::dbufs::video::IVideoBuf::raw_ptr buf, std::vector< std::uint8_t >& _out)
{
  U3_CHECK (buf, "empty source buf for copy to zip buf");
  auto const _raw_buf = buf->get_cbuf ();
  const auto size_buf = (*buf)[utils::dbufs::MemVars::size_data];
  U3_ASSERT (_raw_buf);
  U3_ASSERT (size_buf);

  if (!_raw_buf || !size_buf)
  {
    return;
  }

  _out.resize (size_buf);

  ::libs::helpers::mem::u3copy (_raw_buf, &_out[0], size_buf);
}
}   // namespace utils::dbufs::video::helpers
