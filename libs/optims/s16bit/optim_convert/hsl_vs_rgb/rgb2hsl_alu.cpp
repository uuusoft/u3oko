//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       
*\author    Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
*\create    27.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim_convert
*\brief     Набор функция для конвертации HSL <---> RGB16
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "rgb_to_hsl_int.hpp"

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {

const float _epsilon = 1.0f / (256.0f * 2.0f);

inline void
rgb2hsl (
  const unsigned char& _r,
  const unsigned char& _g,
  const unsigned char& _b,
  float&               _h,
  float&               _s,
  float&               _l)
{
  float       _nr                 = _r * ::libs::optim::s16bit::consts::f_d1_to_d255;      //Where RGB values = 0 ? 255
  float       _ng                 = _g * ::libs::optim::s16bit::consts::f_d1_to_d255;
  float       _nb                 = _b * ::libs::optim::s16bit::consts::f_d1_to_d255;
  float       _min_rgb            = std::min<float> (_nr, std::min<float> (_ng, _nb));      //Min. value of RGB
  float       _max_rgb            = std::max<float> (_nr, std::max<float> (_ng, _nb));      //Max. value of RGB
  const float _delta_max_min      = _max_rgb - _min_rgb;                                    //Delta RGB value
  const float _sum_max_min        = _max_rgb + _min_rgb;
  const float _1_to_delta_max_min = 1.0f / _delta_max_min;

  _l = _sum_max_min * 0.5f;

  if (_delta_max_min == 0.0f)      //This is a gray, no chroma...
    {
      _h = 0.0f;      //HSL results = 0 ? 1
      _s = 0.0f;

      return;
    }

  //Chromatic data...

  if (_l < 0.5f)
    {
      _s = _delta_max_min / _sum_max_min;
    }
  else
    {
      _s = _delta_max_min / (2.0f - _sum_max_min);
    }

  //_s = 1.0f;//debug

  if (std::fabs (_max_rgb - _nr) <= _epsilon)
    {
      if (_ng >= _nb)
        {
          _h = ::libs::optim::s16bit::consts::f_d1_to_d6 * (_ng - _nb) * _1_to_delta_max_min;
        }
      else
        {
          _h = ::libs::optim::s16bit::consts::f_d1_to_d6 * (_ng - _nb) * _1_to_delta_max_min + 1.0f;
        }
    }
  else if (std::fabs (_max_rgb - _ng) <= _epsilon)
    {
      _h = ::libs::optim::s16bit::consts::f_d1_to_d6 * (_nb - _nr) * _1_to_delta_max_min + ::libs::optim::s16bit::consts::f_d1_to_d3;
    }
  else
    {
      UASSERT (std::fabs (_max_rgb - _nb) <= _epsilon);

      _h = ::libs::optim::s16bit::consts::f_d1_to_d6 * (_nr - _ng) * _1_to_delta_max_min + ::libs::optim::s16bit::consts::f_d2_to_d3;
    }

  return;
}


void
rgb24_to_hsl_alu (::libs::optim::MCallInfo& _info)
{
  RGB2HSL_PREFIX (1);

  _leak_hsl;      //workaround error C2220

  const std::size_t    _stride_hsl = _info.dsts_[0].stride_;
  const unsigned char* _rgb24str   = UUU_MEM_CAST<const unsigned char*> (_rgb24);
  float                _sh         = 0.0f;
  float                _ss         = 0.0f;
  float                _sl         = 0.0f;

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          rgb2hsl (
            _rgb24str[2], _rgb24str[1], _rgb24str[0], _sh, _ss, _sl);

          _h[_indxx] = ::libs::helpers::utils::ret_check_bound<short> (_sh * 255.0f, 0, 255);
          _s[_indxx] = ::libs::helpers::utils::ret_check_bound<short> (_ss * 255.0f, 0, 255);
          _l[_indxx] = ::libs::helpers::utils::ret_check_bound<short> (_sl * 255.0f, 0, 255);

          _rgb24str += 3 * _ppc;
        }

      _rgb24str += _leak_rgb;

      FAST_MOVE_PTR (_h, _stride_hsl);
      FAST_MOVE_PTR (_s, _stride_hsl);
      FAST_MOVE_PTR (_l, _stride_hsl);
    }
  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb
