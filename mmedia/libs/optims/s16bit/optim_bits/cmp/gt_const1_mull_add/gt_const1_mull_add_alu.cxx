/**
\file       gt_const1_mull_add_alu.cxx
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_libs_bits
*/

namespace libs::optim::s16bit::bits::cmp::gt_const1_mull_add
{

#ifndef SET_UNALIGNED_FUNCT

void
alu (::libs::optim::io::MCallInfo& info)
{
  // D[i] = D[i] + D[i] * D[i] *(S[i] > Const1 ? 1 : 0 )

  picter_dim_type number_sub_pixel_x = 0;
  picter_dim_type number_sub_pixel_y = 0;
  picter_dim_type leak_stride_source = 0;
  picter_dim_type leak_stride_dest   = 0;

  calc_dest_source_dims (
    info.dsts_[0].stride_,
    info.srcs_[0].stride_,
    info.dsts_[0].width_,
    info.dsts_[0].height_,
    4,
    number_sub_pixel_x,
    number_sub_pixel_y,
    leak_stride_source,
    leak_stride_dest);

  U3_ASSERT (0 < number_sub_pixel_y);

  const std::int16_t* source = info.srcs_[0].buf ();
  std::int16_t*       dest   = info.dsts_[0].buf ();
  picter_dim_type     stride = info.dsts_[0].stride_;
  picter_dim_type     width  = info.dsts_[0].width_;
  picter_dim_type     height = info.dsts_[0].height_;
  // const std::uint16_t*	mask_dest8	= info.params_.dest_mask_;
  const std::int16_t  const1  = info.params_.consts_[0][0];
  const std::int16_t* bsource = source;
  std::int16_t*       bdest   = dest;

  for (picter_dim_type indxy = 0; indxy < height; ++indxy)
  {
    for (picter_dim_type indxx = 0; indxx < width; ++indxx)
    {
      bdest[indxx] += (bsource[indxx] > const1 ? bdest[indxx] * bdest[indxx] : 0);
    }

    bsource = ::libs::helpers::mem::move_cptr (bsource, stride);
    bdest   = ::libs::helpers::mem::move_ptr (bdest, stride);
  }
}

#endif

}   // namespace libs::optim::s16bit::bits::cmp::gt_const1_mull_add
