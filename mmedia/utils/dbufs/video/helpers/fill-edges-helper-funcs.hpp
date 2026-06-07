#pragma once
/**
\file       fill-edges-helper-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_dbufs
\brief      Объявление вспомогательных функции подгтовки буфера к операции свертка
*/

namespace utils::dbufs::video::helpers
{
/// Функция синхронизирует окаймление буфера с его содержимым
/// \param[in,out]  buf буфер, выделенный с учетом поддержки операции "свертка"
/// \return         true при успехе
inline void
fill_edges (IVideoBuf::raw_ptr buf)
{
  U3_CHECK (buf, "empty buf");
  U3_CHECK (buf->get_flag (BufFlags::convolution_support), "- operation topb_convolution_buf not support");
  U3_CHECK (buf->get_flag (BufFlags::convolution_data), "- data not support convlution");

  const auto    buf_width  = buf->get_dim_var (Dims::width);
  const auto    buf_height = buf->get_dim_var (Dims::height);
  const auto    buf_stride = buf->get_dim_var (Dims::stride);
  std::uint8_t* buf_beg    = buf->get_buf () + (*buf)[MemVars::offset_data];

  for (std::uint32_t _yindx = 0; _yindx < buf_height; ++_yindx)
  {
    const std::int32_t _xshorts = ::libs::optim::s16bit::conv::consts::bufs::x_off_edge_conv / sizeof (std::int16_t);
    std::uint8_t*      _str_buf = buf_beg + buf_stride * _yindx;
    auto*              _fstrb   = ::libs::helpers::casts::reinterpret_cast_helper< std::int16_t* > (_str_buf);
    auto*              _bstrb   = ::libs::helpers::casts::reinterpret_cast_helper< std::int16_t* > (_str_buf - 2);

    for (std::int32_t _xindx = 0; _xindx < U3_CAST_INT32 (_xshorts); ++_xindx)
    {
      _bstrb[-_xindx] = _fstrb[_xindx];
    }

    auto* _fstrf = ::libs::helpers::casts::reinterpret_cast_helper< std::int16_t* > (_str_buf + buf_width * sizeof (std::int16_t) - 2);
    auto* _bstrf = ::libs::helpers::casts::reinterpret_cast_helper< std::int16_t* > (_str_buf + buf_width * sizeof (std::int16_t));

    for (std::int32_t _xindx = 0; _xindx < U3_CAST_INT32 (_xshorts); ++_xindx)
    {
      _bstrf[_xindx] = _fstrf[-_xindx];
    }
  }

  for (std::uint32_t _yindx = 0; _yindx < ::libs::optim::s16bit::conv::consts::bufs::half_max_size_core_conv; ++_yindx)
  {
    std::uint8_t* _str_buf = buf_beg;
    auto*         _fstrb   = ::libs::helpers::casts::reinterpret_cast_helper< std::int16_t* > (_str_buf + buf_stride * (_yindx + 0) - ::libs::optim::s16bit::conv::consts::bufs::x_off_edge_conv);
    auto*         _bstrb   = ::libs::helpers::casts::reinterpret_cast_helper< std::int16_t* > (_str_buf - buf_stride * (_yindx + 1) - ::libs::optim::s16bit::conv::consts::bufs::x_off_edge_conv);

    ::libs::helpers::mem::u3copy (_fstrb, _bstrb, buf_stride);
  }

  for (std::uint32_t _yindx = 0; _yindx < ::libs::optim::s16bit::conv::consts::bufs::half_max_size_core_conv; ++_yindx)
  {
    std::uint8_t* _str_buf = buf_beg + buf_stride * buf_height;
    auto*         _fstrb   = ::libs::helpers::casts::reinterpret_cast_helper< std::int16_t* > (_str_buf - buf_stride * (_yindx + 1) - ::libs::optim::s16bit::conv::consts::bufs::x_off_edge_conv);
    auto*         _bstrb   = ::libs::helpers::casts::reinterpret_cast_helper< std::int16_t* > (_str_buf + buf_stride * (_yindx + 0) - ::libs::optim::s16bit::conv::consts::bufs::x_off_edge_conv);

    ::libs::helpers::mem::u3copy (_fstrb, _bstrb, buf_stride);
  }
}
}   // namespace utils::dbufs::video::helpers
