#pragma once
/**
\file       yuy2_rgb24_int.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/

#if !defined(YUY22RGB24_PREFIX)
#define YUY22RGB24_PREFIX                                                                          \
  const ProxyBuff* _yuy2  = 0;                                                                     \
  ProxyBuff*       _rgb24 = 0;                                                                     \
                                                                                                   \
  get_params (_info, &_yuy2, &_rgb24);                                                             \
                                                                                                   \
  const unsigned char* _yuy2_buff  = _yuy2->ubuff ();                                              \
  unsigned char*       _rgb24_buff = _rgb24->ubuff ();                                             \
  const unsigned int   _leak_yuy2  = _yuy2->stride_ - _yuy2->width_ * sizeof (unsigned char) * 2;  \
  const unsigned int   _leak_rgb24 = _rgb24->stride_ - _yuy2->width_ * sizeof (unsigned char) * 3; \
  const std::size_t    _width      = _yuy2->width_;                                                \
  const std::size_t    _height     = _yuy2->height_;

#endif
