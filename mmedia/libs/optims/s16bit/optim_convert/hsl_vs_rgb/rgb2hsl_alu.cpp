/**
\file       rgb2hsl_alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create     27.11.2016
\project    u3_optim_convert
\brief      Набор функция для конвертации HSL <---> RGB16
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "rgb_to_hsl_int.hpp"

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
const float epsilon = 1.0f / (256.0f * 2.0f);

inline void
rgb2hsl (
  const std::uint8_t& r,
  const std::uint8_t& g,
  const std::uint8_t& b,
  float&              h,
  float&              s,
  float&              l)
{
  float       nr                  = r * ::libs::optim::s16bit::consts::f_d1_to_d255;      // Where RGB values = 0 ? 255
  float       ng                  = g * ::libs::optim::s16bit::consts::f_d1_to_d255;      //
  float       nb                  = b * ::libs::optim::s16bit::consts::f_d1_to_d255;      //
  float       min_rgb             = std::min< float > (nr, std::min< float > (ng, nb));   // Min. value of RGB
  float       max_rgb             = std::max< float > (nr, std::max< float > (ng, nb));   // Max. value of RGB
  const float delta_max_min       = max_rgb - min_rgb;                                    // Delta RGB value
  const float sum_max_min         = max_rgb + min_rgb;                                    //
  const float _1_to_delta_max_min = 1.0f / delta_max_min;                                 //

  l = sum_max_min * 0.5f;

  if (delta_max_min == 0.0f)   // This is a gray, no chroma...
  {
    h = 0.0f;   // HSL results = 0 ? 1
    s = 0.0f;
    return;
  }

  // Chromatic data...
  if (l < 0.5f)
  {
    s = delta_max_min / sum_max_min;
  }
  else
  {
    s = delta_max_min / (2.0f - sum_max_min);
  }

#if 0
  // debug
  s = 1.0f;
#endif

  if (std::fabs (max_rgb - nr) <= epsilon)
  {
    if (ng >= nb)
    {
      h = ::libs::optim::s16bit::consts::f_d1_to_d6 * (ng - nb) * _1_to_delta_max_min;
    }
    else
    {
      h = ::libs::optim::s16bit::consts::f_d1_to_d6 * (ng - nb) * _1_to_delta_max_min + 1.0f;
    }
  }
  else if (std::fabs (max_rgb - ng) <= epsilon)
  {
    h = ::libs::optim::s16bit::consts::f_d1_to_d6 * (nb - nr) * _1_to_delta_max_min + ::libs::optim::s16bit::consts::f_d1_to_d3;
  }
  else
  {
    U3_ASSERT (std::fabs (max_rgb - nb) <= epsilon);
    h = ::libs::optim::s16bit::consts::f_d1_to_d6 * (nr - ng) * _1_to_delta_max_min + ::libs::optim::s16bit::consts::f_d2_to_d3;
  }
}


void
rgb24_to_hsl_alu (::libs::optim::io::MCallInfo& info)
{
  RGB2HSL_PREFIX (1);
  U3_MARK_UNUSED_HERE (leak_hsl);

  const std::uint32_t stride_hsl = info.dsts_[0].stride_;
  const std::uint8_t* rgb24str   = U3_CAST_REINTERPRET< const std::uint8_t* > (rgb24);
  float               sh         = 0.0f;
  float               ss         = 0.0f;
  float               sl         = 0.0f;

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      rgb2hsl (rgb24str[2], rgb24str[1], rgb24str[0], sh, ss, sl);

      h[indxx] = ::libs::helpers::utils::ret_check_bound< std::int16_t > (sh * 255.0f, 0, 255);
      s[indxx] = ::libs::helpers::utils::ret_check_bound< std::int16_t > (ss * 255.0f, 0, 255);
      l[indxx] = ::libs::helpers::utils::ret_check_bound< std::int16_t > (sl * 255.0f, 0, 255);

      rgb24str += 3 * ppc;
    }

    rgb24str += leak_rgb;

    U3_FAST_MOVE_PTR (h, stride_hsl);
    U3_FAST_MOVE_PTR (s, stride_hsl);
    U3_FAST_MOVE_PTR (l, stride_hsl);
  }
}
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb
