/**
\file       histogram_alu.cpp
\date       01.05.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_statistic
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "histogram1.hpp"
#include "histogram1_int.hpp"

namespace libs::optim::s16bit::statistics::histogram
{
void
alu (::libs::optim::io::MCallInfo& cinfo)
{
  int* out_freqs  = 0;
  int  size_freqs = 0;

  get_params (cinfo, out_freqs, size_freqs);

  const std::int16_t* source = cinfo.srcs_[0].buf ();
  std::size_t         stride = cinfo.srcs_[0].stride_;
  std::size_t         width  = cinfo.srcs_[0].width_;
  std::size_t         height = cinfo.srcs_[0].height_;

  for (std::size_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::size_t indxx = 0; indxx < width; ++indxx)
    {
      const std::int16_t val = ::libs::helpers::utils::ret_check_bound< std::int16_t > (source[indxx], 0, 255);
      out_freqs[val]++;
    }

    U3_FAST_MOVE_CPTR (source, stride);
  }
}
}   // namespace libs::optim::s16bit::statistics::histogram
