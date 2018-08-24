#pragma once
/**
\file       yuy2_y16_int.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/

#if !defined(YUY22Y16_PREFIX)
#define YUY22Y16_PREFIX(_px_per_cycle)                                                          \
  const std::size_t _ppc  = _px_per_cycle;                                                      \
  const std::size_t _dppc = _ppc * 2;                                                           \
  const ProxyBuff*  _yuy2 = 0;                                                                  \
  ProxyBuff*        _y16  = 0;                                                                  \
                                                                                                \
  get_params (_info, &_yuy2, &_y16);                                                            \
                                                                                                \
  const unsigned char* _yuy2_buff  = _yuy2->ubuff ();                                           \
  short*               _y16_buff   = _y16->buff ();                                             \
  const std::size_t    _cycles     = _yuy2->width_ / _ppc;                                      \
  const std::size_t    _full_width = _cycles * _ppc;                                            \
  const int            _leak_yuy2  = _yuy2->stride_ - _full_width * sizeof (unsigned char) * 2; \
  const int            _leak_y16   = _y16->stride_ - _full_width * sizeof (unsigned short);     \
  const std::size_t    _width      = _yuy2->width_;                                             \
  const std::size_t    _height     = _yuy2->height_;                                            \
                                                                                                \
  UASSERT (_leak_yuy2 >= 0);                                                                    \
  UASSERT (_leak_y16 >= 0);

#endif
