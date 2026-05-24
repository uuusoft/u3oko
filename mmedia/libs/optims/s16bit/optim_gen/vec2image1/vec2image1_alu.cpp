/**
\file       vec2image1_alu.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "vec2image1.hpp"
#include "get_params_func.hpp"
#include "helpers_funcs.hpp"

namespace libs::optim::s16bit::gen::vec2image1
{
//  internal typess
typedef std::pair< std::int8_t, std::int8_t > pair_type;

void
alu (::libs::optim::io::MCallInfo& cinfo)
{
  const io::ProxyBuf*                                                          src     = nullptr;
  io::ProxyBuf*                                                                dst     = nullptr;
  ::libs::ievents::props::videos::generic::vec2image::EventBufsInfoVec2Image1* pparams = nullptr;
  std::uint32_t                                                                dindxy  = 0;

  get_params (cinfo, &src, &dst, &pparams);

  const std::int32_t max_mbound = U3_CAST_STATIC< std::int32_t > (pparams->size_block_ / 2);

  for (std::uint32_t indxy = 0; indxy < src->height_; ++indxy)
  {
    std::uint32_t       dindxx = 0;
    const std::int16_t* lsrc   = src->get_cline (indxy);
    std::int16_t*       ldst   = dst->get_line (dindxy);

    for (std::uint32_t indxx = 0; indxx < src->width_; ++indxx)
    {
      const char*     rlsrc = U3_CAST_REINTERPRET< const char* > (&lsrc[indxx]);
      const pair_type rvec (*(rlsrc + 0), *(rlsrc + 1));
      std::int32_t    vx = rvec.first * pparams->mul_koeff_vec_;
      std::int32_t    vy = rvec.second * pparams->mul_koeff_vec_;

      ::libs::helpers::utils::check_bound (vx, -max_mbound, max_mbound);
      ::libs::helpers::utils::check_bound (vy, -max_mbound, max_mbound);

      std::int16_t*       bblock_ldst = &ldst[dindxx];
      const std::uint32_t offy        = (max_mbound - 1) * dst->stride_;
      const std::uint32_t offx        = max_mbound * sizeof (std::int16_t);
      std::int16_t*       mblock_ldst = bblock_ldst;

      U3_FAST_MOVE_PTR (mblock_ldst, offy + offx);

      // const std::int16_t color = U3_CAST_INT16(rand() % 255 );
      // const std::int16_t color = indxy % 128 + indxx % 128;
      // const std::int16_t color = 128 * ( indxx % 2 );
      // const std::int16_t color = rand () % 255;   // (rvec == ::libs::ievents::props::videos::generic::motion_est::consts::inv_vec ? 255 : 0);
      const std::int16_t color = (rvec == ::libs::ievents::props::videos::generic::motion_est::consts::inv_vec ? 255 : 0);

      // if (0 * pparams->size_block_ == indxy && 0 * pparams->size_block_ == indxx)
      {
        fill (
          bblock_ldst,
          dst->stride_,
          color,
          pparams->size_block_,
          pparams->size_block_);
      }

      line (mblock_ldst, dst->stride_, 0, 0, vx, vy);
      dindxx += pparams->size_block_;
    }

    dindxy += pparams->size_block_;
  }
}
}   // namespace libs::optim::s16bit::gen::vec2image1
