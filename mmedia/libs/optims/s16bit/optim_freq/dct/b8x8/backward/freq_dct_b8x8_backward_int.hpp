#pragma once
/**
\file       freq_dct_b8x8_backward_int.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "TCallParams.hpp"
#include "../consts/vals.hpp"
#include "../helpers/mem/funcs_copy_mem_b8x8.hpp"
#include "../helpers/zigzag/funcs_zigzag_b8x8.hpp"
#include "../helpers/pack/funcs_pack_short2byte_b8x8.hpp"
#include "../helpers/quant/CQuant.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::backward
{
void get_params (::libs::optim::io::MCallInfo& info, TCallParams& params);

template< typename TTDCT8x8 >
void
freq_dct_b8x8_backward (::libs::optim::io::MCallInfo& info)
{
  TCallParams params;
  get_params (info, params);

  TTDCT8x8            impl;
  const std::int32_t  active_swidth = (params.psrc_->width_ / b8x8::consts::dim_elements_macroblock) * b8x8::consts::dim_elements_macroblock * sizeof (std::int16_t);
  const std::int32_t  ldleak_width  = params.pdst_->stride_ - active_swidth;
  const std::int16_t* cur_buf       = params.psrc_->buf ();
  std::int16_t*       dbuf          = params.pdst_->buf ();
  std::int32_t&       out_size      = (*params.prets_)[info.indx_thread_].byte_size_;

  U3_ALIGN_DEFAULT std::int16_t src_block[b8x8::consts::count_elements_macroblock];

  out_size = 0;

  (*params.prets_)[info.indx_thread_].beg_dst_ = dbuf;

  for (std::uint32_t indxy = 0; indxy < params.pdst_->height_; indxy += b8x8::consts::dim_elements_macroblock)
  {
    for (std::uint32_t indxx = 0; indxx < params.pdst_->width_; indxx += b8x8::consts::dim_elements_macroblock)
    {
      ::libs::helpers::mem::u3copy (cur_buf, src_block, sizeof (std::int16_t) * b8x8::consts::count_elements_macroblock);
      params.pquanter_->backward (src_block);
      helpers::zigzag::backward (src_block);
      impl (src_block);
      //::libs::helpers::mem::set_buf<short>( src_block, info.indx_thread_ ? 255 : 128, 64 );  //debug

      helpers::mem::backward (
        src_block,
        dbuf,
        params.pdst_->stride_);

      out_size += b8x8::consts::count_elements_macroblock;
      cur_buf += b8x8::consts::count_elements_macroblock;
      dbuf += b8x8::consts::dim_elements_macroblock;
    }

    U3_FAST_MOVE_PTR (dbuf, (b8x8::consts::dim_elements_macroblock - 1) * params.pdst_->stride_ + ldleak_width);
  }

  U3_ASSERT ((*params.prets_)[info.indx_thread_].check ());
}
}   // namespace libs::optim::s16bit::freq::dct::b8x8::backward
