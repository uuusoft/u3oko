//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       hsl_to_rgb_int.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_convert
\brief      empty brief
*/

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {
/**
  \brief  empty brief
  */
inline void
check_hsl2rgb (::libs::optim::MCallInfo& _info)
{
  CHECK_STATE (1 == _info.dsts_.size (), "failed, dst size not equal 1");
  CHECK_STATE (3 == _info.srcs_.size (), "failed, src size not equal 1");
  CHECK_STATE (1 == _info.params_.pints_.size (), "failed, pint not equal 1");

  const ::libs::optim::io::ProxyBuff& _h   = _info.srcs_[0];
  const ::libs::optim::io::ProxyBuff& _s   = _info.srcs_[1];
  const ::libs::optim::io::ProxyBuff& _l   = _info.srcs_[2];
  const ::libs::optim::io::ProxyBuff& _rgb = _info.dsts_[0];

  CHECK_STATE ((_h.width_ == _s.width_) && (_h.width_ == _l.width_) && (_h.width_ == _rgb.width_), "failed, widths not equal");
  CHECK_STATE ((_h.height_ == _s.height_) && (_h.height_ == _l.height_) && (_h.height_ == _rgb.height_), "failed, heights not equal");
  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb


#if !defined(HSL2RGB_PREFIX)
#define HSL2RGB_PREFIX(_size)                                                                     \
                                                                                                  \
  check_hsl2rgb (_info);                                                                          \
  const unsigned int _ppc    = _size;                                                             \
  const std::size_t  _width  = _info.dsts_[0].width_;                                             \
  const std::size_t  _height = _info.dsts_[0].height_;                                            \
  const short*       _h      = _info.srcs_[0].buff ();                                            \
  const short*       _s      = _info.srcs_[1].buff ();                                            \
  const short*       _l      = _info.srcs_[2].buff ();                                            \
  unsigned char*     _rgb24  = _info.dsts_[0].ubuff ();                                           \
  unsigned int       _pcx    = _width / 4;                                                        \
                                                                                                  \
  _pcx = (_pcx * 4 < _width) ? _pcx + 1 : _pcx;                                                   \
                                                                                                  \
  const unsigned int _leak_hsl     = _info.srcs_[0].stride_ - _pcx * 4 * sizeof (unsigned short); \
  const unsigned int _stride_rgb24 = _pcx * 4 * sizeof (unsigned char) * 3;                       \
  int*               _out_stride   = _info.params_.pints_[0];                                     \
                                                                                                  \
  if (0 == *_out_stride)                                                                          \
    {                                                                                             \
      *_out_stride = _stride_rgb24;                                                               \
    }                                                                                             \
                                                                                                  \
  const int _leak_rgb24 = *_out_stride - _stride_rgb24;                                           \
  CHECK_STATE ((_leak_rgb24 >= 0), "failed, leak_rgb less 0");

#endif
