#pragma once
/**
\file       buf_helpers_funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace libs::optim::mcalls::helpers
{
inline void
fill (io::ProxyBuf* buf, const std::int16_t val)
{
  ::libs::utility::checks::throw_ifn (buf);
  for (std::uint32_t indxy = 0; indxy < buf->height_; ++indxy)
  {
    std::int16_t* rbuf = buf->get_line (indxy);
    std::fill (&rbuf[0], &rbuf[buf->width_], val);
  }
}
}   // namespace libs::optim::mcalls::helpers
