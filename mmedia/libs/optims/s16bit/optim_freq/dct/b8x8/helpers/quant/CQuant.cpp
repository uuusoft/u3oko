/**
\file       CQuant.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "mmedia/libs/optims/s16bit/optim_freq/dct/b8x8/consts/vals.hpp"
#include "quant_tables.hpp"
#include "CQuant.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::helpers::quant
{
CQuant::CQuant () :
  koeff_ (-1),
  scale_koeff_ (-1)
{
  update (1);
}


CQuant::~CQuant ()
{
}

/// Convert a user-specified quality rating to a percentage scaling factor
/// for an underlying quantization table, using our recommended scaling curve
/// The input 'quality' factor should be 0 (terrible) to 100 (very good)
int
get_scale_koeff (std::int32_t koeff)
{
  // The basic table is used as-is (scaling 100) for a quality of 50.
  // Qualities 50..100 are converted to scaling percentage 200 - 2*Q;
  // note that at Q=100 the scaling is 0, which will cause jpeg_add_quant_table
  // to make all the table entries 1 (hence, minimum quantization loss).
  // Qualities 1..50 are converted to scaling percentage 5000/Q.

  std::int32_t ret = 0;

  if (koeff < 50)
  {
    ret = 5000 / koeff;
  }
  else
  {
    ret = 200 - koeff * 2;
  }
  return ret;
}


void
CQuant::update (std::int32_t koeff)
{
  U3_ASSERT (koeff >= 1 && koeff <= 100);

  koeff = ::libs::helpers::utils::ret_check_bound< std::int32_t > (koeff, 1, 100);

  if (koeff == koeff_)
  {
    return;
  }

  koeff_       = koeff;
  scale_koeff_ = get_scale_koeff (koeff_);
  //  обновляем таблицы квантования, алгоритм совпадает с алгоритмом из jpeg
  for (std::size_t indx = 0; indx < b8x8::consts::count_elements_macroblock; ++indx)
  {
    const auto& base = consts::lum_quant_table[indx];
    auto&       res  = quant_table_y_[indx];

    res = (base * scale_koeff_ + 0) / 100;
    // res = ( base * scale_koeff_ + 50 ) / 100;
    // res = base;
    // res = 1;
    res = res > 0 ? res : 1;
  }
}


void
CQuant::forward (std::int16_t* buf) const
{
  U3_ASSERT (buf);
  //  проивзодим квантование блока - под MMX данный алгоритм не удастся корреткно перенести - эмулция через сдвиг
  //  дает обратный эффект при декодировании
  for (std::size_t indx = 0; indx < b8x8::consts::count_elements_macroblock; ++indx)
  {
    buf[indx] = buf[indx] / quant_table_y_[indx];
  }
}


void
CQuant::backward (std::int16_t* buf) const
{
  U3_ASSERT (buf);

  for (std::size_t indx = 0; indx < b8x8::consts::count_elements_macroblock; ++indx)
  {
    buf[indx] = buf[indx] * quant_table_y_[indx];
  }
}
}   // namespace libs::optim::s16bit::freq::dct::b8x8::helpers::quant
