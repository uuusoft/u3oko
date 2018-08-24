#pragma once
/**
\file       nv21_y16_int.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/

#if !defined(NV212Y16_PREFIX)
#define NV212Y16_PREFIX(_px_per_cycle)                                                              \
  const std::size_t _ppc = _px_per_cycle;                                                           \
  const ProxyBuff*  _y8  = 0;                                                                       \
  ProxyBuff*        _y16 = 0;                                                                       \
                                                                                                    \
  get_params (_info, &_y8, &_y16);                                                                  \
                                                                                                    \
  const unsigned char* _y8_buff    = _y8->ubuff ();                                                 \
  short*               _y16_buff   = _y16->buff ();                                                 \
  const std::size_t    _stride_y8  = _y8->stride_;                                                  \
  const std::size_t    _stride_y16 = _y16->stride_;                                                 \
  const std::size_t    _leak_y8    = _stride_y8 - _y8->width_ * sizeof (unsigned char) * 1 * _ppc;  \
  const std::size_t    _leak_y16   = _stride_y16 - _y8->width_ * sizeof (unsigned char) * 2 * _ppc; \
  const std::size_t    _width      = _y8->width_;                                                   \
  const std::size_t    _height     = _y8->height_;

#endif
