#pragma once
/**
\file       funcs_copy_mem_b8x8.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_freq
*/
#include "mmedia/libs/optims/s16bit/optim_freq/dct/b8x8/consts/vals.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::helpers::mem
{
inline void
forward (const std::int16_t* in, std::int16_t* out, const std::size_t stride)
{
  U3_ASSERT (out);
  U3_ASSERT (in);
  U3_ASSERT (stride);

  for (std::size_t indxy = 0; indxy < 8; ++indxy)
  {
    for (std::size_t indxx = 0; indxx < 8; ++indxx)
    {
      out[8 * indxy + indxx] = in[indxx];
    }

    U3_FAST_MOVE_CPTR (in, stride);
  }
}


inline void
backward (const std::int16_t* in, std::int16_t* out, const std::size_t stride)
{
  U3_ASSERT (out);
  U3_ASSERT (in);
  U3_ASSERT (stride);

  for (std::size_t indxy = 0; indxy < 8; ++indxy)
  {
    for (std::size_t indxx = 0; indxx < 8; ++indxx)
    {
      out[indxx] = in[8 * indxy + indxx];
    }

    U3_FAST_MOVE_PTR (out, stride);
  }
}

}   // namespace libs::optim::s16bit::freq::dct::b8x8::helpers::mem
