/**
\file       i420_rgb24_alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       05.04.2022
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "mmedia/libs/optims/optim_convert/gen/yuy2_rgb_gen.hpp"
#include "i420_rgb24.hpp"
#include "i420_rgb24_int.hpp"

namespace libs::optim::convert::i420_rgb24
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  const ::libs::optim::io::ProxyBuf* y     = nullptr;
  ::libs::optim::io::ProxyBuf*       rgb24 = nullptr;

  get_params (info, &y, &rgb24);

  const std::uint32_t                off_beg_u          = y->stride_ * y->height_ * (info.count_threads_ - info.indx_thread_);
  const std::uint32_t                size_u_buf         = (y->stride_ * y->height_ * info.count_threads_ >> 1);
  const std::uint32_t                off_beg_v          = off_beg_u + size_u_buf;
  const std::uint32_t                off_uv_thread_bufs = y->stride_ * y->height_ * info.indx_thread_ >> 1;
  const ::libs::optim::io::ProxyBuf  temp_u (y->ubuf () + off_beg_u + off_uv_thread_bufs, y->stride_, y->width_, y->height_ >> 1, "temp_u convert::i420_rgb24");
  const ::libs::optim::io::ProxyBuf  temp_v (y->ubuf () + off_beg_v + off_uv_thread_bufs, y->stride_, y->width_, y->height_ >> 1, "temp_v convert::i420_rgb24");
  const ::libs::optim::io::ProxyBuf* pbu = &temp_u;
  const ::libs::optim::io::ProxyBuf* pbv = &temp_v;

  const std::uint8_t* y_buf      = y->ubuf ();
  const std::uint8_t* u_buf      = pbu->ubuf ();
  const std::uint8_t* v_buf      = pbv->ubuf ();
  std::uint8_t*       rgb24_buf  = rgb24->ubuf ();
  const auto          width      = y->width_;
  const auto          height     = y->height_;
  const std::uint32_t leak_y     = y->stride_ - width * sizeof (std::uint8_t) * 1;
  const std::uint32_t leak_uv    = y->stride_ - ((width * sizeof (std::uint8_t) * 1) >> 1);
  const std::uint32_t leak_rgb24 = rgb24->stride_ - width * sizeof (std::uint8_t) * 3;

  for (std::uint32_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::uint32_t indx_x = 0; indx_x < width; indx_x += 2)
    {
      const auto         y1        = U3_CAST_INT16 (y_buf[0]) - 16;
      const auto         y2        = U3_CAST_INT16 (y_buf[1]) - 16;
      const auto         u         = U3_CAST_INT16 (u_buf[0]) - 128;
      const auto         v         = U3_CAST_INT16 (v_buf[0]) - 128;
      const std::int32_t y1_premul = y1 * 4769;
      const std::int32_t y2_premul = y2 * 4769;

#ifdef U3_FAKE_DISABLE
      // debug
      rgb24_buf[0] = y1;
      rgb24_buf[1] = y1;
      rgb24_buf[2] = y1;

      rgb24_buf[3] = y2;
      rgb24_buf[4] = y2;
      rgb24_buf[5] = y2;
#else
      rgb24_buf[0] = gen::short2char (::libs::optim::convert::gen::yuv2red (y1_premul, u, v));
      rgb24_buf[1] = gen::short2char (::libs::optim::convert::gen::yuv2green (y1_premul, u, v));
      rgb24_buf[2] = gen::short2char (::libs::optim::convert::gen::yuv2blue (y1_premul, u, v));

      rgb24_buf[3] = gen::short2char (::libs::optim::convert::gen::yuv2red (y2_premul, u, v));
      rgb24_buf[4] = gen::short2char (::libs::optim::convert::gen::yuv2green (y2_premul, u, v));
      rgb24_buf[5] = gen::short2char (::libs::optim::convert::gen::yuv2blue (y2_premul, u, v));
#endif
      rgb24_buf += 6;
      y_buf += 2;
      u_buf += 1;
      v_buf += 1;
    }

    y_buf += leak_y;
    rgb24_buf += leak_rgb24;
    u_buf += leak_uv;
    v_buf += leak_uv;

    if (!(indx_y & 1))
    {
      u_buf -= y->stride_;
      v_buf -= y->stride_;
    }
  }
}
}   // namespace libs::optim::convert::i420_rgb24
