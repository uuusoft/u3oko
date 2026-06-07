/**
\file
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "base_7x7.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::conv::base::c7x7
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
  ret += px_res (csstr, mask, sindx, 3);
  ret += px_res (csstr, mask, sindx, 4);
  ret += px_res (csstr, mask, sindx, 5);
  ret += px_res (csstr, mask, sindx, 6);
  return ret;
}


struct TSse2CalcObj {
  TSse2CalcObj () = default;

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
    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    tres += str_res (csstr, mask, 1);
    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    tres += str_res (csstr, mask, 2);
    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    tres += str_res (csstr, mask, 3);
    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    tres += str_res (csstr, mask, 4);
    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    tres += str_res (csstr, mask, 5);
    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    tres += str_res (csstr, mask, 6);
    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);
  }
};


struct TModSse2CalcObj : public TSse2CalcObj {
  TModSse2CalcObj () = default;

  void
  init (::libs::optim::io::MCallInfo& info, const cores::values_core_type** pmask)
  {
    TSse2CalcObj::init (info, pmask);
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
    TSse2CalcObj::get_res (mul_koeff, csstr, mask, stride, tress, dstr);
    tress[0] = std::abs (tress[0]);
  }
};


void
mod_sse2 (::libs::optim::io::MCallInfo& info)
{
  move_alg< TModSse2CalcObj, cores::values_core_type, TPostProcessor, consts::size_core > (info);
}


void
sse2 (::libs::optim::io::MCallInfo& info)
{
  move_alg< TSse2CalcObj, cores::values_core_type, TPostProcessor, consts::size_core > (info);
}
}   // namespace libs::optim::s16bit::conv::base::c7x7

#endif
