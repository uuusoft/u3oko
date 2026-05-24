#pragma once
/**
\file       lib-optim-s16bit-def-bufs.hpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_ops
*/

namespace libs::optim::s16bit::consts
{
// clang-format off
U3_ALIGN_DEFAULT
constexpr std::uint16_t us_all_xffff[32] = {
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
};

U3_ALIGN_DEFAULT
constexpr std::int16_t s_all_d0[32] = {
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0
};

U3_ALIGN_DEFAULT
constexpr std::int16_t s_all_d1[32] = {
  1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1
};

U3_ALIGN_DEFAULT
constexpr std::int16_t s_all_d2[32] = {
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2
};

U3_ALIGN_DEFAULT
constexpr std::int16_t s_all_d3[32] = {
  3, 3, 3, 3, 3, 3, 3, 3, 
  3, 3, 3, 3, 3, 3, 3, 3, 
  3, 3, 3, 3, 3, 3, 3, 3, 
  3, 3, 3, 3, 3, 3, 3, 3
};

U3_ALIGN_DEFAULT
constexpr std::int16_t s_all_d5[32] = {
  5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5
};

U3_ALIGN_DEFAULT
constexpr std::int16_t s_all_d128[32] = {
  128, 128, 128, 128, 128, 128, 128, 128, 
  128, 128, 128, 128, 128, 128, 128, 128, 
  128, 128, 128, 128, 128, 128, 128, 128, 
  128, 128, 128, 128, 128, 128, 128, 128
};

U3_ALIGN_DEFAULT
constexpr std::int16_t s_all_d255[32] = {
  255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255
};

U3_ALIGN_DEFAULT
constexpr std::int16_t s_once_d1[32] = {
  1, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0
};
// clang-format on
}   // namespace libs::optim::s16bit::consts
