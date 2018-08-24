#pragma once
/**
\file       rgb_to_l_int.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_convert
\brief      empty brief
*/

#if !defined(RGB2L_PREFIX)
#define RGB2L_PREFIX(_size)                                                                                  \
  CHECK_CALL (check_rgb2l (_info), "failed check rgb2l info");                                               \
  const unsigned int  _ppc            = _size;                                                               \
  short*              _l              = _info.dsts_[0].buff ();                                              \
  const unsigned int* _rgb24          = UUU_MEM_CAST<const unsigned int*> (_info.srcs_[0].ubuff ());         \
  const std::size_t   _width          = _info.srcs_[0].width_;                                               \
  const std::size_t   _height         = _info.srcs_[0].height_;                                              \
  const unsigned int  _raw_cycle      = _width / _ppc;                                                       \
  const unsigned int  _cycle          = (_raw_cycle * _ppc < _width) ? _raw_cycle + 1 : _raw_cycle;          \
  const unsigned int  _leak_rgb       = _info.srcs_[0].stride_ - _cycle * _ppc * sizeof (unsigned char) * 3; \
  const unsigned int  _req_stride_hsl = _cycle * sizeof (unsigned short) * _ppc;                             \
  const unsigned int  _leak_hsl       = _info.dsts_[0].stride_ - _req_stride_hsl;

#endif
