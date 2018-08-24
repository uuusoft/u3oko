//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       l_to_rgb_int.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_convert
\brief      empty brief
*/

#if !defined(L2RGB_PREFIX)
#define L2RGB_PREFIX(_size)                                                                       \
                                                                                                  \
  CHECK_CALL (check_l2rgb (_info), "failed check l2rgb");                                         \
                                                                                                  \
  const unsigned int _ppc    = _size;                                                             \
  const std::size_t  _width  = _info.dsts_[0].width_;                                             \
  const std::size_t  _height = _info.dsts_[0].height_;                                            \
  const short*       _l      = _info.srcs_[0].buff ();                                            \
  unsigned char*     _rgb24  = _info.dsts_[0].ubuff ();                                           \
  unsigned int       _pcx    = _width / 4;                                                        \
                                                                                                  \
  _pcx = (_pcx * 4 < _width) ? _pcx + 1 : _pcx;                                                   \
                                                                                                  \
  const unsigned int _leak_l       = _info.srcs_[0].stride_ - _pcx * 4 * sizeof (unsigned short); \
  const unsigned int _stride_rgb24 = _pcx * 4 * sizeof (unsigned char) * 3;                       \
  int*               _out_stride   = _info.params_.pints_[0];                                     \
                                                                                                  \
  if (0 == *_out_stride)                                                                          \
    {                                                                                             \
      *_out_stride = _stride_rgb24;                                                               \
    }                                                                                             \
                                                                                                  \
  const int _leak_rgb24 = *_out_stride - _stride_rgb24;                                           \
                                                                                                  \
  CHECK_STATE ((_leak_rgb24 >= 0), "failed, leak_rgb less 0");

#endif
