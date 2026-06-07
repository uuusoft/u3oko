/**
\file       gt_const_alu.cxx
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_libs_bits
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "gt_const.hpp"
#include "gt_const_int.hpp"

namespace libs::optim::s16bit::bits::cmp::gt_const
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  const std::uint16_t* mask_dest8 = 0;
  std::int16_t         const1     = 0;
  std::int16_t         const2     = 0;

  get_params (info, mask_dest8, const1, const2);

  std::int16_t*   dest   = info.dsts_[0].buf ();
  picter_dim_type stride = info.dsts_[0].stride_;
  picter_dim_type width  = info.dsts_[0].width_;
  picter_dim_type height = info.dsts_[0].height_;
  std::int16_t*   bdest  = dest;

  for (picter_dim_type indxy = 0; indxy < height; ++indxy)
  {
    for (picter_dim_type indxx = 0; indxx < width; ++indxx)
    {
      bdest[indxx] = bdest[indxx] > const1 ? const2 : 0;
    }

    bdest = ::libs::helpers::mem::move_ptr (bdest, stride);
  }
}

}   // namespace libs::optim::s16bit::bits::cmp::gt_const
