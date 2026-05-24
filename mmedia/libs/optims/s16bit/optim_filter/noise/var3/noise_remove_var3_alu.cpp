/**
\file       noise_remove_var3_alu.cpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_filter
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "noise_remover3_x86.hpp"

namespace libs::optim::s16bit::filter::noise::var3
{

void
alu (::libs::optim::io::MCallInfo& info)
{
  std::array< int, 2 >* bound_koeffs       = 0;
  std::array< int, 3 >* koeffs_remove      = 0;
  std::array< int, 1 >* bound_cond_koeffs  = 0;
  std::array< int, 1 >* koeffs_cond_remove = 0;

  get_params (info, bound_koeffs, koeffs_remove, bound_cond_koeffs, koeffs_cond_remove);

#if 0
    std::int16_t exp_bounds[4] =
    {
      U3_CAST_INT16( (*bound_koeffs)[0] ),
      U3_CAST_INT16( (*bound_koeffs)[1] ),
      U3_CAST_INT16( (*bound_cond_koeffs)[0] ),
      U3_CAST_INT16( (*koeffs_cond_remove )[0] )
    };
#endif
#if 0
    std::int16_t exp_koeffs[4] =
    {
      (*koeffs_remove )[0], (*koeffs_remove )[1], (*koeffs_remove )[2], 0
    };

    std::size_t loc_leak_stride = 0;

    calc_dest_dims ( info.srcs_[0].stride_, info.srcs_[0].width_, loc_leak_stride, 4 );
#endif

  std::int16_t*       cur_data   = info.srcs_[0].buf ();
  const std::int16_t* cond_buf   = info.srcs_[1].buf ();
  std::int16_t*       prev_data  = info.dsts_[0].buf ();
  std::size_t         stride     = info.srcs_[0].stride_;
  std::size_t         width      = info.srcs_[0].width_;
  std::size_t         height     = info.srcs_[0].height_;
  std::int16_t*       bcur_data  = cur_data;
  const std::int16_t* bcond_buf  = cond_buf;
  std::int16_t*       bprev_data = prev_data;

  for (std::size_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::size_t indxx = 0; indxx < width; ++indxx)
    {
      if (bcond_buf[indxx] > 0)
      {
        bprev_data[indxx] = bcur_data[indxx];
      }
      else
      {
        bcur_data[indxx] = bprev_data[indxx];
      }
    }

    U3_FAST_MOVE_CPTR (bcond_buf, stride);
    U3_FAST_MOVE_PTR (bcur_data, stride);
    U3_FAST_MOVE_PTR (bprev_data, stride);
  }
}

}   // namespace libs::optim::s16bit::filter::noise::var3
