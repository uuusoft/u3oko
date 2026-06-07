#pragma once
/**
\file       bits_two_source_move_alg.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_libs_bits
*/

namespace libs::optim::s16bit::bits::two_source
{
struct TParams {
  public:
  TParams () = default;

  void
  reset ()
  {
    sbuf_   = 0;
    width_  = 0;
    height_ = 0;
    dbuf_   = 0;
    stride_ = 0;
  }

  const std::int16_t* sbuf_   = nullptr;   //<
  std::int16_t*       dbuf_   = nullptr;   //<
  std::size_t         width_  = 0;         //<
  std::size_t         height_ = 0;         //<
  std::size_t         stride_ = 0;         //<
};


inline void
get_params (::libs::optim::io::MCallInfo& info, TParams& params)
{
  params.reset ();

  U3_CHECK (1 == info.srcs_.size (), "1 != info.srcs_.size ()");
  U3_CHECK (1 == info.dsts_.size (), "1 != info.dsts_.size ()");

  auto& dst = info.dsts_[0];

  params.width_  = dst.width_;
  params.height_ = dst.height_;
  params.dbuf_   = dst.buf ();
  params.stride_ = dst.stride_;
  params.sbuf_   = info.srcs_[0].buf ();
}


template< typename TTFiller, std::size_t count_ppc = 1 >
void
move_alg (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT (count_ppc > 0);
  U3_ASSERT (count_ppc <= 32);

  TTFiller filling;
  TParams  params;

  get_params (info, params);

  filling.init (params);

  const std::int16_t* sstr = params.sbuf_;
  std::int16_t*       dstr = params.dbuf_;

  for (std::size_t indxy = 0; indxy < params.height_; ++indxy)
  {
    for (std::size_t indxx = 0; indxx < params.width_; indxx += count_ppc)
    {
      filling.update (sstr + indxx, dstr + indxx);
    }

    sstr = ::libs::helpers::mem::move_cptr (sstr, params.stride_);
    dstr = ::libs::helpers::mem::move_ptr (dstr, params.stride_);
  }
}
}   // namespace libs::optim::s16bit::bits::two_source
