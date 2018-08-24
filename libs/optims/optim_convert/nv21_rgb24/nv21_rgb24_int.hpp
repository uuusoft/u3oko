#pragma once
/**
\file       nv21_rgb24_int.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/

#if !defined(NV212RGB24_PREFIX)
#define NV212RGB24(_px_per_cycle)                                                                                  \
  const std::size_t _ppc   = _px_per_cycle;                                                                        \
  const ProxyBuff*  _yuy2  = 0;                                                                                    \
  ProxyBuff*        _rgb24 = 0;                                                                                    \
                                                                                                                   \
  get_params (_info, &_yuy2, &_rgb24);                                                                             \
                                                                                                                   \
  const std::size_t    _off_beg_uv = _yuy2->width_ * _yuy2->height_ * (_info.count_threads_ - _info.indx_thread_); \
  const std::size_t    _off_uv     = _yuy2->width_ * (_yuy2->height_ >> 1) * _info.indx_thread_;                   \
  const unsigned char* _y_buff     = _yuy2->ubuff ();                                                              \
  const unsigned char* _uv_buff    = _yuy2->ubuff () + _off_beg_uv + _off_uv;                                      \
  unsigned char*       _rgb24_buff = _rgb24->ubuff ();                                                             \
  const unsigned int   _leak_yuy2  = _yuy2->stride_ - _yuy2->width_ * sizeof (unsigned char) * 1;                  \
  const unsigned int   _leak_rgb24 = _rgb24->stride_ - _yuy2->width_ * sizeof (unsigned char) * 3;                 \
  bool                 _odd_line   = true;

#endif
