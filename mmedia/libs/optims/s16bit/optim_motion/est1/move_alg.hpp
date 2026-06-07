#pragma once
/**
\file     move_alg.hpp
\author   Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date     12.09.2016
\project  u3_optim_libs_motion
\brief    Оценка движения в кадре
*/
#include "vals.hpp"

namespace libs::optim::s16bit::motion::est1
{
/// Алгоритм обхода данных для вычисления разности между двумя кадрами
/// \tparam         CalculatorType  тип калькулятора, объекта который производит вычисления над данными для оценки движения в кадре
/// \param[in, out] info           параметры данных (буфер, размер, параметры алгоритма etc
template< typename CalculatorType >
void
move_alg (::libs::optim::io::MCallInfo& info)
{
  CalculatorType          calcs;
  EventBufsInfoMotionEst* pparams  = nullptr;
  const io::ProxyBuf*     cur_src  = nullptr;
  const io::ProxyBuf*     prev_src = nullptr;
  io::ProxyBuf*           dst_vecs = nullptr;

  get_params (info, &cur_src, &prev_src, &dst_vecs, &pparams);

  // optim::mcalls::helpers::fill (dst_vecs, rand () % 255);
  optim::mcalls::helpers::fill (dst_vecs, 0);

  std::uint32_t offy   = info.indx_thread_ * cur_src->height_;
  std::uint32_t leaky  = (info.count_threads_ - info.indx_thread_ - 1) * cur_src->height_;
  std::uint32_t dindxy = 0;

  calcs.init (info);

  for (std::uint32_t indxy = 0; indxy < cur_src->height_; indxy += pparams->size_block_)
  {
    std::uint32_t dindxx = 0;
    std::int16_t* ldst   = dst_vecs->get_line (dindxy);

    ++dindxy;
    if (indxy + pparams->size_block_ >= cur_src->height_ + leaky)
    {
      continue;
    }

    for (std::uint32_t indxx = 0; indxx < cur_src->width_; indxx += pparams->size_block_)
    {
      const std::int16_t*     cur_ssrc = &cur_src->get_cline (indxy)[indxx];
      std::int32_t            diff     = std::numeric_limits< std::int32_t >::max ();
      char*                   rldst    = ::libs::helpers::casts::reinterpret_cast_helper< char* > (&ldst[dindxx]);
      std::pair< char, char > rvec     = ::libs::ievents::props::videos::generic::motion_est::consts::inv_vec;

      ++dindxx;

      if (indxx + pparams->size_block_ >= cur_src->width_)
      {
        continue;
      }

      for (std::size_t indxv = 0; indxv < pparams->search_vecs_.size (); ++indxv)
      {
        const auto& ivec   = pparams->search_vecs_[indxv];
        auto        pindxx = U3_CAST_INT32 (indxx) + ivec.first;
        auto        pindxy = U3_CAST_INT32 (indxy) + ivec.second;

        if (pindxx < 0 || pindxy < 0)
        {
          continue;
        }

        if (pindxx + pparams->size_block_ >= U3_CAST_INT32 (cur_src->width_) ||
            pindxy + pparams->size_block_ >= U3_CAST_INT32 (cur_src->height_ /*+ leaky*/))
        {
          continue;
        }

        if (U3_CAST_INT32 (offy) + pindxy < 0)
        {
          continue;
        }
#if 1
        const std::int16_t* prev_ssrc  = &prev_src->get_cline (pindxy, true)[pindxx];
        const std::int32_t  block_diff = calcs.get_res (cur_ssrc, prev_ssrc, pparams->size_block_, cur_src->stride_);

        if (block_diff < pparams->max_error_)
        {
          if (block_diff < diff)
          {
            diff = block_diff;
            rvec = ivec;

            if (diff <= pparams->min_error_)
            {
              break;
            }
          }
        }
#endif
      }

      *(rldst + 0) = rvec.first;
      *(rldst + 1) = rvec.second;

      //*(rldst + 0) = -16;   // rand() % 255 > 120 ? -200 : 200;
      //*(rldst + 1) = 16;    // rand() % 255 > 120 ? 200 : -200;
    }
  }
}
}   // namespace libs::optim::s16bit::motion::est1
