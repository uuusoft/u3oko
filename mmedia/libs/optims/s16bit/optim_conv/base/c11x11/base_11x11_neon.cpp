/**
\file       base_11x11_neon.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017

\project    u3_optim_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "base_11x11.hpp"

#if defined(U3_CPU_ARM)

namespace libs::optim::s16bit::conv::base::c11x11
{
inline int
px_res (
  const std::int16_t* csstr,
  const cores::TCore* mask,
  const std::uint32_t sindx,
  std::uint32_t       pxindx)
{
  return U3_CAST_INT32 (csstr[pxindx]) * mask->get (pxindx, sindx);
}

inline int
str_res (
  const std::int16_t* csstr,
  const cores::TCore* mask,
  const std::uint32_t sindx)
{
  std::int32_t ret = 0;
  ret += px_res (csstr, mask, sindx, 0);
  ret += px_res (csstr, mask, sindx, 1);
  ret += px_res (csstr, mask, sindx, 2);
  ret += px_res (csstr, mask, sindx, 3);
  ret += px_res (csstr, mask, sindx, 4);
  ret += px_res (csstr, mask, sindx, 5);
  ret += px_res (csstr, mask, sindx, 6);
  ret += px_res (csstr, mask, sindx, 7);
  ret += px_res (csstr, mask, sindx, 8);
  ret += px_res (csstr, mask, sindx, 9);
  ret += px_res (csstr, mask, sindx, 10);
  return ret;
}


struct TNeonCalcObj {
  TNeonCalcObj ()
  {
  }

  void
  init (::libs::optim::io::MCallInfo& info, const cores::TCore** pmask)
  {
  }

  void
  get_res (
    const std::int16_t  mul_koeff,
    const std::int16_t* csstr,
    const cores::TCore* mask,
    const std::uint32_t stride,
    std::int32_t*       tress,
    std::int16_t*       dstr)
  {
    std::int32_t& tres = *tress;

    tres = 0;

    tres += str_res (csstr, mask, 0);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 1);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 2);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 3);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 4);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 5);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 6);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 7);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 8);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 9);
    U3_FAST_MOVE_CPTR (csstr, stride);

    tres += str_res (csstr, mask, 10);
    U3_FAST_MOVE_CPTR (csstr, stride);
  }
};


struct TModNeonCalcObj : public TNeonCalcObj {
  TModNeonCalcObj ()
  {
  }

  void
  init (::libs::optim::io::MCallInfo& info, const cores::TCore** pmask)
  {
    TNeonCalcObj::init (info, pmask);
  }

  void
  get_res (
    const std::int16_t  mul_koeff,
    const std::int16_t* csstr,
    const cores::TCore* mask,
    const std::uint32_t stride,
    std::int32_t*       tress,
    std::int16_t*       dstr)
  {
    TNeonCalcObj::get_res (mul_koeff, csstr, mask, stride, tress, dstr);
    tress[0] = std::abs (tress[0]);
  }
};


void
mod_neon (::libs::optim::io::MCallInfo& info)
{
  move_alg< TModNeonCalcObj, cores::TCore, TPostProcessor, consts::size_core > (info);
}


void
neon (::libs::optim::io::MCallInfo& info)
{
  move_alg< TNeonCalcObj, cores::TCore, TPostProcessor, consts::size_core > (info);
}
}   // namespace libs::optim::s16bit::conv::base::c11x11

#endif
