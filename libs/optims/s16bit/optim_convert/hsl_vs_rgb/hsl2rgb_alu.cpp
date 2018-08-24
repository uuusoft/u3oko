//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       
*\author    Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
*\create    27.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim
*\brief     Набор функция для конвертации HSL <---> RGB16
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "hsl_to_rgb_int.hpp"

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {

inline float
hue2rgb (
  const float& v1,
  const float& v2,
  float&       vH)
{
  if (vH < 0.0f)
    {
      vH += 1.0f;
    }

  if (vH > 1.0f)
    {
      vH -= 1.0f;
    }

  if ((6.0f * vH) < 1.0f)
    {
      return (v1 + (v2 - v1) * 6.0f * vH);
    }

  if ((2.0f * vH) < 1.0f)
    {
      return (v2);
    }

  if ((3.0f * vH) < 2.0f)
    {
      return (v1 + (v2 - v1) * (::libs::optim::s16bit::consts::f_d2_to_d3 - vH) * 6.0f);
    }

  return v1;
}
/**
  \brief    Функция конвертирует HSL->RGB24.
  */
inline void
hsl2rgb (
  unsigned char& _r,
  unsigned char& _g,
  unsigned char& _b,
  const float&   _h,
  const float&   _s,
  const float&   _l)
{
  if (_s == 0.0f)      //HSL values = 0 ? 1
    {
      const unsigned char _val = static_cast<unsigned char> (255.0f * _l);

      _r = _val;      //RGB results = 0 ? 255
      _g = _val;
      _b = _val;

      return;
    }

  float var_2 = 0.0f;

  if (_l < 0.5f)
    {
      var_2 = _l * (1.0f + _s);
    }
  else
    {
      var_2 = (_l + _s) - (_s * _l);
    }

  float var_1 = 2.0f * _l - var_2;

  float var_3 = _h + ::libs::optim::s16bit::consts::f_d1_to_d3;
  _r          = static_cast<unsigned char> (255.0f * hue2rgb (var_1, var_2, var_3));

  var_3 = _h;
  _g    = static_cast<unsigned char> (255.0f * hue2rgb (var_1, var_2, var_3));

  var_3 = _h - ::libs::optim::s16bit::consts::f_d1_to_d3;
  _b    = static_cast<unsigned char> (255.0f * hue2rgb (var_1, var_2, var_3));

  return;
}


void
hsl_to_rgb24_alu (::libs::optim::MCallInfo& _info)
{
  HSL2RGB_PREFIX (1);

  float _sh = 0.0f;
  float _ss = 0.0f;
  float _sl = 0.0f;

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          _sh = _h[0] * ::libs::optim::s16bit::consts::f_d1_to_d255;
          _ss = _s[0] * ::libs::optim::s16bit::consts::f_d1_to_d255;
          _sl = _l[0] * ::libs::optim::s16bit::consts::f_d1_to_d255;

#if defined(UUU_CPU_X86)
          hsl2rgb (_rgb24[2], _rgb24[1], _rgb24[0], _sh, _ss, _sl);
#else
          hsl2rgb (_rgb24[0], _rgb24[1], _rgb24[2], _sh, _ss, _sl);
#endif

          _h++;
          _s++;
          _l++;

          _rgb24 += 3;
        }

      FAST_MOVE_CPTR (_h, _leak_hsl);
      FAST_MOVE_CPTR (_s, _leak_hsl);
      FAST_MOVE_CPTR (_l, _leak_hsl);

      _rgb24 += _leak_rgb24;
    }
  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb
