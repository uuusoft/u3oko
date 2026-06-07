/**
\file       hsl2rgb_alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create     27.11.2016
\project    u3_optim_libs
\brief      Набор функция для конвертации HSL <---> RGB16
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "hsl_to_rgb_int.hpp"

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
inline float
hue2rgb (const float& v1, const float& v2, float& vH)
{
  if (vH < 0.0F)
  {
    vH += 1.0F;
  }

  if (vH > 1.0F)
  {
    vH -= 1.0F;
  }

  if ((6.0F * vH) < 1.0F)
  {
    return (v1 + (v2 - v1) * 6.0F * vH);
  }

  if ((2.0F * vH) < 1.0F)
  {
    return (v2);
  }

  if ((3.0F * vH) < 2.0F)
  {
    return (v1 + (v2 - v1) * (::libs::optim::s16bit::consts::f_d2_to_d3 - vH) * 6.0F);
  }

  return v1;
}

/// Функция конвертирует HSL->RGB24
inline void
hsl2rgb (
  std::uint8_t& r,
  std::uint8_t& g,
  std::uint8_t& b,
  const float&  h,
  const float&  s,
  const float&  l)
{
  if (s == 0.0F)   // HSL values = 0 ? 1
  {
    const auto val = U3_CAST_UINT8 (255.0F * l);

    r = val;   // RGB results = 0 ? 255
    g = val;
    b = val;
    return;
  }

  float var_2 = 0.0F;

  if (l < 0.5f)
  {
    var_2 = l * (1.0F + s);
  }
  else
  {
    var_2 = (l + s) - (s * l);
  }

  float var_1 = 2.0F * l - var_2;
  float var_3 = h + ::libs::optim::s16bit::consts::f_d1_to_d3;

  r = U3_CAST_UINT8 (255.0F * hue2rgb (var_1, var_2, var_3));

  var_3 = h;
  g     = U3_CAST_UINT8 (255.0F * hue2rgb (var_1, var_2, var_3));

  var_3 = h - ::libs::optim::s16bit::consts::f_d1_to_d3;
  b     = U3_CAST_UINT8 (255.0F * hue2rgb (var_1, var_2, var_3));
}


void
hsl_to_rgb24_alu (::libs::optim::io::MCallInfo& info)
{
  HSL2RGB_PREFIX (1);

  float sh = 0.0F;
  float ss = 0.0F;
  float sl = 0.0F;

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      sh = h[0] * ::libs::optim::s16bit::consts::f_d1_to_d255;
      ss = s[0] * ::libs::optim::s16bit::consts::f_d1_to_d255;
      sl = l[0] * ::libs::optim::s16bit::consts::f_d1_to_d255;

#ifdef U3_CPU_X86
      hsl2rgb (rgb24[2], rgb24[1], rgb24[0], sh, ss, sl);
#else
      hsl2rgb (rgb24[0], rgb24[1], rgb24[2], sh, ss, sl);
#endif

      h++;
      s++;
      l++;

      rgb24 += 3;
    }

    h = ::libs::helpers::mem::move_cptr (h, leak_hsl);
    s = ::libs::helpers::mem::move_cptr (s, leak_hsl);
    l = ::libs::helpers::mem::move_cptr (l, leak_hsl);

    rgb24 += leak_rgb24;
  }
}
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb
