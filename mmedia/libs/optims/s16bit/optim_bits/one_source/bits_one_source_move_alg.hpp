#pragma once
/**
\file       bits_one_source_move_alg.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.07.2017
\project    u3_optim_libs_bits
*/

namespace libs::optim::s16bit::bits::one_source
{
struct TParams final {
  public:
  TParams () = default;

  void
  reset ()
  {
    width_   = 0;
    height_  = 0;
    dbuf_    = 0;
    stride_  = 0;
    filling_ = 0;
  }

  std::int16_t* dbuf_    = nullptr;   //<
  std::size_t   width_   = 0;         //<
  std::size_t   height_  = 0;         //<
  std::size_t   stride_  = 0;         //<
  std::int16_t  filling_ = 0;         //<
};


inline void
get_params (::libs::optim::io::MCallInfo& info, TParams& params)
{
  params.reset ();

  U3_CHECK (1 == info.params_.evals_.size (), "1 != info.params_.evals_.size ()");
  U3_CHECK (0 == info.srcs_.size (), "0 != info.srcs_.size ()");
  U3_CHECK (1 == info.dsts_.size (), "1 != info.dsts_.size ()");

  auto& dst = info.dsts_[0];

  params.width_   = dst.width_;
  params.height_  = dst.height_;
  params.dbuf_    = dst.buf ();
  params.stride_  = dst.stride_;
  params.filling_ = boost::any_cast< std::int16_t > (info.params_.evals_[0]);
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

  std::int16_t* dstr = params.dbuf_;

  for (std::size_t indxy = 0; indxy < params.height_; ++indxy)
  {
    for (std::size_t indxx = 0; indxx < params.width_; indxx += count_ppc)
    {
      filling.update (dstr + indxx);
    }

    dstr = ::libs::helpers::mem::move_ptr (dstr, params.stride_);
  }
}
}   // namespace libs::optim::s16bit::bits::one_source
