/**
\file       scale_wdown_b2x2_alu.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_scale
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "scale_wdown_b2x2.hpp"
#include "scale_wdown_b2x2_int.hpp"

namespace libs::optim::s16bit::scale::fixed::wdown::b2x2
{
struct TScalerALU final {
  void
  operator() (CallParams& params)
  {
    U3_ASSERT_SIGNAL ("failed");
#if 0
      const std::size_t istride  = params.psrc_->stride_ >> 1;

      const std::size_t ostride  = (*params.stride_output_ ) >> 1;      
      const int*      pindxrow = (*params.indxer_->get_indxrow() ).get_as<int>();
      const int*      pindxcol = (*params.indxer_->get_indxcol() ).get_as<int>();
      const short*    psrc   = params.psrc_->buf ();
      short*        pdst   = params.pdst_->buf ();

      for (std::size_t indxy = 0; indxy < params.pdst_->height_; ++indxy)
      {
        for (std::size_t indxx = 0; indxx < params.pdst_->width_; ++indxx )
        {
          pdst[ indxy * ostride + indxx ] = psrc[ pindxrow[indxy] * istride + pindxcol[indxx] ];
        }
      }
#endif
  }
};


void
alu (::libs::optim::io::MCallInfo& info)
{
  b2b_scale< TScalerALU > (info);
}
}   // namespace libs::optim::s16bit::scale::fixed::wdown::b2x2
