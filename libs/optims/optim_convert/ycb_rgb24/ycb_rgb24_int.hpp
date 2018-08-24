#pragma once
/**
\file       ycb_rgb24_int.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       30.07.2018
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/

#if !defined(YCB2RGB24_PREFIX)
#define YCB2RGB24_PREFIX                                                                   \
  const ProxyBuff* _yuy2  = nullptr;                                                       \
  ProxyBuff*       _rgb24 = nullptr;                                                       \
                                                                                           \
  get_params (_info, &_yuy2, &_rgb24);                                                     \
                                                                                           \
  const unsigned char* _yuy2_buff  = _yuy2->ubuff ();                                      \
  unsigned char*       _rgb24_buff = _rgb24->ubuff ();                                     \
  const std::size_t    _width      = _yuy2->width_;                                        \
  const std::size_t    _height     = _yuy2->height_;                                       \
  const unsigned int   _leak_yuy2  = _yuy2->stride_ - _width * sizeof (unsigned char) * 2; \
  const unsigned int   _leak_rgb24 = _rgb24->stride_ - _width * sizeof (unsigned char) * 3;

#endif
