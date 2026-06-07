/**
\file     motion_est1_alu.cpp
\author   Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date     28.08.2016
\project  u3_optim_libs_motion
\brief    Оценка движения
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "motion_est1.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buf_helpers_funcs.hpp"
#include "move_alg.hpp"

namespace libs::optim::s16bit::motion::est1
{

struct TAluCalcObj final {
  TAluCalcObj () = default;

  void
  init (::libs::optim::io::MCallInfo& info)
  {
  }

  std::int32_t
  get_res (
    const std::int16_t* src1,
    const std::int16_t* src2,
    const std::int16_t  size_block,
    const std::size_t   stride)
  {
    std::int32_t ret = 0;
    for (std::size_t indxy = 0; indxy < U3_CAST_SIZE_T (size_block); ++indxy)
    {
      for (std::size_t indxx = 0; indxx < U3_CAST_SIZE_T (size_block); ++indxx)
      {
        int iret = src1[indxx] - src2[indxx];
        ret += std::abs (iret);   // SAD
        // ret+= iret * iret;   //SSD
      }

      src1 = ::libs::helpers::mem::move_cptr (src1, stride);
      src2 = ::libs::helpers::mem::move_cptr (src2, stride);
    }
    return ret;
  }
};


void
alu (::libs::optim::io::MCallInfo& info)
{
  move_alg< TAluCalcObj > (info);
}
}   // namespace libs::optim::s16bit::motion::est1
