/**
\file       count_if_ge_alu.cpp
\date       01.05.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_statistic
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "count_if_ge.hpp"
#include "count_if_ge_int.hpp"

namespace libs::optim::s16bit::statistics::count_if_ge
{
void
alu (::libs::optim::io::MCallInfo& cinfo)
{
  std::int32_t* pcount = 0;
  std::int16_t  bound  = 0;

  get_params (cinfo, pcount, bound);

  *pcount = 0;

  const std::int16_t* source = cinfo.srcs_[0].buf ();
  const auto          stride = cinfo.srcs_[0].stride_;
  const auto          width  = cinfo.srcs_[0].width_;
  const auto          height = cinfo.srcs_[0].height_;

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; ++indxx)
    {
      (*pcount) += source[indxx] >= bound ? 1 : 0;
    }

    U3_FAST_MOVE_CPTR (source, stride);
  }
}
}   // namespace libs::optim::s16bit::statistics::count_if_ge
