#pragma once
/**
\file       yuy2_rgb_gen.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_optim_gen_convert
*/

namespace libs::optim::convert::gen
{
inline std::uint8_t
short2char (short val)
{
  return U3_CAST_UINT8 (val < 0 ? 0 : (val > 255 ? 255 : val));
}

inline short
yuv2red (const std::int32_t& y, const std::int16_t& u, const std::int16_t& v)
{
  return U3_CAST_INT16 ((y + v * 6537 + 0) >> 12);
}

inline short
yuv2green (const std::int32_t& y, const std::int16_t& u, const std::int16_t& v)
{
  return U3_CAST_INT16 ((y - u * 1605 - v * 3330) >> 12);
}

inline short
yuv2blue (const std::int32_t& y, const std::int16_t& u, const std::int16_t& v)
{
  return U3_CAST_INT16 ((y + u * 8391) >> 12);
}

inline short
rgb2y (const std::int16_t& r, const std::int16_t& g, const std::int16_t& b)
{
  return U3_CAST_INT16 (((66 * r + 129 * g + 25 * b) >> 8) + 16);
}

inline short
rgb2u (const std::int16_t& r, const std::int16_t& g, const std::int16_t& b)
{
  return U3_CAST_INT16 (((-38 * r - 74 * g + 112 * b) >> 8) + 128);
}

inline short
rgb2v (const std::int16_t& r, const std::int16_t& g, const std::int16_t& b)
{
  return U3_CAST_INT16 (((112 * r - 94 * g - 18 * b) >> 8) + 128);
}
}   // namespace libs::optim::convert::gen
