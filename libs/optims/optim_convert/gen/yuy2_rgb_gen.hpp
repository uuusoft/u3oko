#pragma once
/**
\file       yuy2_rgb_gen.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/

namespace libs { namespace optim { namespace convert { namespace gen {

inline unsigned char
short2char (short _val)
{
  return UUU_ICAST_UCHAR (_val < 0 ? 0 : (_val > 255 ? 255 : _val));
}


inline short
yuv2red (const int& _y, const short& _u, const short& _v)
{
  return UUU_ICAST_SHORT ((_y + _v * 6537 + 0) >> 12);
}


inline short
yuv2green (const int& _y, const short& _u, const short& _v)
{
  return UUU_ICAST_SHORT ((_y - _u * 1605 - _v * 3330) >> 12);
}


inline short
yuv2blue (const int& _y, const short& _u, const short& _v)
{
  return UUU_ICAST_SHORT ((_y + _u * 8391) >> 12);
}


inline short
rgb2y (const short& _r, const short& _g, const short& _b)
{
  return UUU_ICAST_SHORT (((66 * _r + 129 * _g + 25 * _b) >> 8) + 16);
}


inline short
rgb2u (const short& _r, const short& _g, const short& _b)
{
  return UUU_ICAST_SHORT (((-38 * _r - 74 * _g + 112 * _b) >> 8) + 128);
}


inline short
rgb2v (const short& _r, const short& _g, const short& _b)
{
  return UUU_ICAST_SHORT (((112 * _r - 94 * _g - 18 * _b) >> 8) + 128);
}

}}}}      // namespace libs::optim::convert::gen
