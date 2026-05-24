/**
\file       base_3x3_alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "base_3x3.hpp"

namespace libs::optim::s16bit::conv::base::c3x3
{
inline int
px_res (
  const std::int16_t*            csstr,
  const cores::values_core_type* mask,
  const std::uint32_t            sindx,
  std::uint32_t                  pxindx)
{
  return U3_CAST_INT32 (csstr[pxindx]) * mask->get (pxindx, sindx);
}


inline int
str_res (
  const std::int16_t*            csstr,
  const cores::values_core_type* mask,
  const std::uint32_t            sindx)
{
  std::int32_t ret = 0;

  ret += px_res (csstr, mask, sindx, 0);
  ret += px_res (csstr, mask, sindx, 1);
  ret += px_res (csstr, mask, sindx, 2);
  return ret;
}


struct TAluCalcObj {
  TAluCalcObj ()
  {
  }

  void
  init (::libs::optim::io::MCallInfo& info, const cores::values_core_type** pmask)
  {
  }

  void
  get_res (
    const std::int16_t             mul_koeff,
    const std::int16_t*            csstr,
    const cores::values_core_type* mask,
    const std::uint32_t            stride,
    std::int32_t*                  tress,
    std::int16_t*                  dstr)
  {
    std::int32_t& tres = *tress;

    tres = 0;

    tres += str_res (csstr, mask, 0);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 1);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 2);
    U3_FAST_MOVE_CPTR (csstr, stride);
  }
};


struct TModAluCalcObj : public TAluCalcObj {
  TModAluCalcObj ()
  {
  }

  void
  init (::libs::optim::io::MCallInfo& info, const cores::values_core_type** pmask)
  {
    TAluCalcObj::init (info, pmask);
  }

  void
  get_res (
    const std::int16_t             mul_koeff,
    const std::int16_t*            csstr,
    const cores::values_core_type* mask,
    const std::uint32_t            stride,
    std::int32_t*                  tress,
    std::int16_t*                  dstr)
  {
    TAluCalcObj::get_res (mul_koeff, csstr, mask, stride, tress, dstr);
    tress[0] = std::abs (tress[0]);
  }
};


void
mod_alu (::libs::optim::io::MCallInfo& info)
{
  return move_alg< TModAluCalcObj, cores::values_core_type, TPostProcessor, consts::size_core > (info);
}


void
alu (::libs::optim::io::MCallInfo& info)
{
  move_alg< TAluCalcObj, cores::values_core_type, TPostProcessor, consts::size_core > (info);
}
}   // namespace libs::optim::s16bit::conv::base::c3x3
