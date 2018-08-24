#pragma once
/**
\file       fill_convolution_edges.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление вспомогательных функции подгтовки буфера к операции свертка.
*/

namespace utils { namespace dbuffs { namespace video { namespace helpers {
/**
  \brief          Функция синхронизирует окаймление буфера с его содержимым.
  \param[in,out]  _buff буфер, выделенный с учетом поддержки операции "свертка".
  */
inline void
fill_convolution_edges (IVideoBuff::raw_ptr _buff)
{
  CHECK_STATE (_buff, "failed, empty buff");
  CHECK_STATE (_buff->get_flag (TypeFlagsBuff::convolution_support), "failed, operation topb_convolution_buffer not support");
  CHECK_STATE (_buff->get_flag (TypeFlagsBuff::convolution_data), "failed, data not support convlution");

  const auto     _buff_width  = _buff->get_dim_var (TypeDimVar::width);
  const auto     _buff_height = _buff->get_dim_var (TypeDimVar::height);
  const auto     _buff_stride = _buff->get_dim_var (TypeDimVar::stride);
  unsigned char* _buff_beg    = _buff->get_buff () + (*_buff)[TypeMemVar::offset_data];

  for (int _yindx = 0; _yindx < _buff_height; ++_yindx)
    {
      const int      _xshorts  = cs16buffs::x_off_edge_conv / sizeof (short);
      unsigned char* _str_buff = _buff_beg + _buff_stride * _yindx;
      short*         _fstrb    = UUU_MEM_CAST<short*> (_str_buff);
      short*         _bstrb    = UUU_MEM_CAST<short*> (_str_buff - 2);

      for (int _xindx = 0; _xindx < UUU_ICAST_INT (_xshorts); ++_xindx)
        {
          _bstrb[-_xindx] = _fstrb[_xindx];
        }

      short* _fstrf = UUU_MEM_CAST<short*> (_str_buff + _buff_width * sizeof (short) - 2);
      short* _bstrf = UUU_MEM_CAST<short*> (_str_buff + _buff_width * sizeof (short));

      for (int _xindx = 0; _xindx < UUU_ICAST_INT (_xshorts); ++_xindx)
        {
          _bstrf[_xindx] = _fstrf[-_xindx];
        }
    }

  for (int _yindx = 0; _yindx < cs16buffs::half_max_size_core_conv; ++_yindx)
    {
      unsigned char* _str_buff = _buff_beg;
      short*         _fstrb    = UUU_MEM_CAST<short*> (_str_buff + _buff_stride * (_yindx + 0) - cs16buffs::x_off_edge_conv);
      short*         _bstrb    = UUU_MEM_CAST<short*> (_str_buff - _buff_stride * (_yindx + 1) - cs16buffs::x_off_edge_conv);

      smem::acopy (_fstrb, _bstrb, _buff_stride);
    }

  for (int _yindx = 0; _yindx < cs16buffs::half_max_size_core_conv; ++_yindx)
    {
      unsigned char* _str_buff = _buff_beg + _buff_stride * _buff_height;
      short*         _fstrb    = UUU_MEM_CAST<short*> (_str_buff - _buff_stride * (_yindx + 1) - cs16buffs::x_off_edge_conv);
      short*         _bstrb    = UUU_MEM_CAST<short*> (_str_buff + _buff_stride * (_yindx + 0) - cs16buffs::x_off_edge_conv);

      smem::acopy (_fstrb, _bstrb, _buff_stride);
    }
  return;
}

}}}}      // namespace utils::dbuffs::video::helpers
