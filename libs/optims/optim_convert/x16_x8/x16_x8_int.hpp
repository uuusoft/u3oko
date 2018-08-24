//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       x16_x8_int.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/

namespace libs { namespace optim { namespace convert { namespace x16_x8 {

void get_params (
  ::libs::optim::MCallInfo& _info,
  const ProxyBuff**         _x16,
  ProxyBuff**               _x8);

}}}}      // namespace libs::optim::convert::x16_x8

#if !defined(X16_TO_X8_PREFIX)
#define X16_TO_X8_PREFIX(_px_per_cycle)                                                    \
  const std::size_t _ppc  = _px_per_cycle;                                                 \
  const std::size_t _dppc = _ppc * 1;                                                      \
  const ProxyBuff*  _x16  = nullptr;                                                       \
  ProxyBuff*        _x8   = nullptr;                                                       \
                                                                                           \
  get_params (_info, &_x16, &_x8);                                                         \
                                                                                           \
  const short*      _x16_buff   = _x16->buff ();                                           \
  unsigned char*    _x8_buff    = _x8->ubuff ();                                           \
  const std::size_t _cycles     = _x16->width_ / _ppc;                                     \
  const std::size_t _full_width = _cycles * _ppc;                                          \
  const int         _leak_x16   = _x16->stride_ - _full_width * sizeof (short) * 1;        \
  const int         _leak_x8    = _x8->stride_ - _full_width * sizeof (unsigned char) * 1; \
  const std::size_t _width      = _x16->width_;                                            \
  const std::size_t _height     = _x16->height_;                                           \
                                                                                           \
  UASSERT (_leak_x16 >= 0);                                                                \
  UASSERT (_leak_x8 >= 0);

#endif
