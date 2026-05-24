#pragma once
/**
\file       optim-conv-move_alg.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.09.2016
\project    u3_optim_conv
\brief      Алгоритм прохода по данным для свертки двумерного сигнала
*/
#include "iconv-core.hpp"

namespace libs::optim::s16bit::conv
{
template< typename TTCore >
short
get_mkoeff_core (const TTCore& mask, const std::int32_t override_summ = 0)
{
  const std::int32_t ksumm = override_summ ? override_summ : mask.summ ();

  if (0 == ksumm)
  {
    return conv::consts::base_mul_koeff;
  }

  const std::int16_t pre_ret  = conv::consts::base_mul_koeff / ksumm;
  std::int16_t       ret      = pre_ret;
  const std::int32_t pr_summ1 = ret * ksumm;

  if (pr_summ1 < conv::consts::base_mul_koeff)
  {
    const std::int32_t pr_summ2 = (ret + 1) * ksumm;
    if ((conv::consts::base_mul_koeff - pr_summ1) > (pr_summ2 - conv::consts::base_mul_koeff))
    {
      ++ret;
    }
  }
  return ret;
}


template< typename TTCore >
struct TTParams {
  void
  get_params (
    ::libs::optim::io::MCallInfo& info,
    const TTCore*&                mask,
    std::int16_t&                 mul_koeff)
  {
    U3_CHECK (2 == info.params_.evals_.size (), "2 != info.params_.evals_.size ()");
    U3_CHECK (1 == info.srcs_.size (), "1 != info.srcs_.size ()");
    U3_CHECK (1 == info.dsts_.size (), "1 != info.dsts_.size ()");

    mask      = boost::any_cast< const TTCore* > (info.params_.evals_[0]);
    mul_koeff = boost::any_cast< std::int16_t > (info.params_.evals_[1]);

    U3_CHECK (mask, "empty mask");
  }
};


struct TEmptyPostProcessor final {
  TEmptyPostProcessor ()
  {
  }

  void
  update (
    std::int16_t  mul_koeff,
    std::uint32_t count_ppc,
    std::uint32_t indxx,
    std::int32_t* tres,
    std::int16_t* dstr)
  {
  }
};


struct TPostProcessor final {
  TPostProcessor ()
  {
  }

  void
  update (
    std::int16_t  mul_koeff,
    std::uint32_t count_ppc,
    std::uint32_t indxx,
    std::int32_t* tres,
    std::int16_t* dstr)
  {
    for (std::uint32_t indxr = 0; indxr < count_ppc; ++indxr)
    {
      tres[indxr]         = (tres[indxr] * mul_koeff) >> U3_SHIFT_MUL_KOEFF_CONVOLUTION;
      tres[indxr]         = tres[indxr] > 255 ? 255 : tres[indxr];
      tres[indxr]         = tres[indxr] < -255 ? -255 : tres[indxr];
      dstr[indxx + indxr] = U3_CAST_INT16 (tres[indxr]);
    }
  }
};


template<
  typename CalculatorType,
  typename TTCore,
  typename TTPostProcessor       = TPostProcessor,
  std::uint32_t size_core        = 3,
  std::uint32_t count_ppc        = 1,
  std::uint32_t count_reserv_ppc = 0 >
void
move_alg (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT (count_ppc > 0);
  U3_ASSERT (count_ppc <= 16);

  TTParams< TTCore > params;
  CalculatorType     calcs;
  const TTCore*      mask      = 0;
  std::int16_t       mul_koeff = 0;

  params.get_params (info, mask, mul_koeff);

  U3_ALIGN_DEFAULT int tres[count_ppc + count_reserv_ppc];
  TTPostProcessor      post_obj;
  const auto&          src       = info.srcs_[0];
  const std::uint32_t  width     = src.width_;
  const std::uint32_t  height    = src.height_;
  const std::int16_t*  sbuf      = src.buf ();
  std::int16_t*        dbuf      = info.dsts_[0].buf ();
  const std::uint32_t  stride    = src.stride_;
  const std::int16_t*  sstr      = sbuf;
  std::int16_t*        dstr      = dbuf;
  const std::uint32_t  hmsize    = size_core >> 1;
  const std::uint32_t  move_size = hmsize * stride;

  calcs.init (info, &mask);

  std::fill (&tres[0], &tres[std::size (tres)], 0);

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += count_ppc)
    {
      const std::int16_t* csstr = sstr + indxx - hmsize;
      U3_FAST_MOVE_CPTR_BACK (csstr, move_size);
      calcs.get_res (mul_koeff, csstr, mask, stride, tres, dstr + indxx);
      post_obj.update (mul_koeff, count_ppc, indxx, tres, dstr);
    }

    U3_FAST_MOVE_CPTR (sstr, stride);
    U3_FAST_MOVE_PTR (dstr, stride);
  }
}
}   // namespace libs::optim::s16bit::conv
