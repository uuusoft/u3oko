#pragma once
/**
\file       flip_y_move_alg.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_libs_block
*/

namespace libs::optim::s16bit::block::flip_y
{
struct TParams final {
  public:
  TParams () = default;

  void
  reset ()
  {
    width_  = 0;
    height_ = 0;
    dbuf_   = 0;
    stride_ = 0;
  }

  std::uint8_t* dbuf_   = nullptr;   //<
  std::size_t   width_  = 0;         //<
  std::size_t   height_ = 0;         //<
  std::size_t   stride_ = 0;         //<
};


inline void
get_params (::libs::optim::io::MCallInfo& info, TParams& params)
{
  params.reset ();

  U3_CHECK (0 == info.srcs_.size (), "1 != info.srcs_.size ()");
  U3_CHECK (1 == info.dsts_.size (), "1 != info.dsts_.size ()");

  auto& dst = info.dsts_[0];

  params.width_  = dst.width_;
  params.height_ = dst.height_;
  params.dbuf_   = dst.ubuf ();
  params.stride_ = dst.stride_;
}


template< typename TTFlipper, std::size_t count_bts >
void
move_alg (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT (count_bts > 0);
  U3_ASSERT (count_bts <= 64);

  TTFlipper flipper;
  TParams   params;

  get_params (info, params);

  flipper.init (params);

  const std::size_t cnt_y = params.height_ >> 1;
  std::uint8_t*     str1  = params.dbuf_;
  std::uint8_t*     str2  = params.dbuf_ + (params.height_ - 1) * params.stride_;

  for (std::size_t indxy = 0; indxy < cnt_y; ++indxy)
  {
    for (std::size_t indxx = 0; indxx < params.stride_; indxx += count_bts)
    {
      flipper.update (&str1[indxx], &str2[indxx]);
    }


    str1 = ::libs::helpers::mem::move_ptr (str1, params.stride_);
    str2 = ::libs::helpers::mem::move_ptr_back (str2, params.stride_);
  }
}
}   // namespace libs::optim::s16bit::block::flip_y
