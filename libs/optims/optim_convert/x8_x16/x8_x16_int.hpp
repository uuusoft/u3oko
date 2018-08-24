//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       x8_x16_int.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/

namespace libs { namespace optim { namespace convert { namespace x8_x16 {

void get_params (
  ::libs::optim::MCallInfo& _info,
  const ProxyBuff**         _x16,
  ProxyBuff**               _x8);

}}}}      // namespace libs::optim::convert::x8_x16

#if !defined(X8_TO_X16_PREFIX)
#define X8_TO_X16_PREFIX(_px_per_cycle)                                                       \
  const std::size_t _ppc  = _px_per_cycle;                                                    \
  const std::size_t _dppc = _ppc * 1;                                                         \
  const ProxyBuff*  _x8   = nullptr;                                                          \
  ProxyBuff*        _x16  = nullptr;                                                          \
                                                                                              \
  get_params (_info, &_x8, &_x16);                                                            \
                                                                                              \
  const unsigned char* _x8_buff    = _x8->ubuff ();                                           \
  short*               _x16_buff   = _x16->buff ();                                           \
  const std::size_t    _cycles     = _x16->width_ / _ppc;                                     \
  const std::size_t    _full_width = _cycles * _ppc;                                          \
  const int            _leak_x16   = _x16->stride_ - _full_width * sizeof (short) * 1;        \
  const int            _leak_x8    = _x8->stride_ - _full_width * sizeof (unsigned char) * 1; \
  const std::size_t    _width      = _x16->width_;                                            \
  const std::size_t    _height     = _x16->height_;                                           \
                                                                                              \
  UASSERT (_leak_x16 >= 0);                                                                   \
  UASSERT (_leak_x8 >= 0);

#endif
