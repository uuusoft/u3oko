#pragma once
/**
\file       lib-optim-s16bit-def-bufs-f32.hpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_ops
*/

namespace libs::optim::s16bit::consts
{
constexpr float f_d0 = 0.0F;

// clang-format off
U3_ALIGN_DEFAULT
constexpr float f_all_d0[32] = {
  f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, 
  f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, 
  f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, 
  f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0
};

constexpr float f_d1 = 1.0F;

U3_ALIGN_DEFAULT
constexpr float f_all_d1[32] = {
  f_d1, f_d1, f_d1, f_d1, f_d1, f_d1, f_d1, f_d1, 
  f_d1, f_d1, f_d1, f_d1, f_d1, f_d1, f_d1, f_d1, 
  f_d1, f_d1, f_d1, f_d1, f_d1, f_d1, f_d1, f_d1, 
  f_d1, f_d1, f_d1, f_d1, f_d1, f_d1, f_d1, f_d1
};

constexpr float f_d2 = 2.0F;

U3_ALIGN_DEFAULT
constexpr float f_all_d2[32] = {
  f_d2, f_d2, f_d2, f_d2, f_d2, f_d2, f_d2, f_d2, 
  f_d2, f_d2, f_d2, f_d2, f_d2, f_d2, f_d2, f_d2, 
  f_d2, f_d2, f_d2, f_d2, f_d2, f_d2, f_d2, f_d2, 
  f_d2, f_d2, f_d2, f_d2, f_d2, f_d2, f_d2, f_d2
};

constexpr float f_d3 = 3.0F;

U3_ALIGN_DEFAULT
constexpr float f_all_d3[32] = {
  f_d3, f_d3, f_d3, f_d3, f_d3, f_d3, f_d3, f_d3, 
  f_d3, f_d3, f_d3, f_d3, f_d3, f_d3, f_d3, f_d3, 
  f_d3, f_d3, f_d3, f_d3, f_d3, f_d3, f_d3, f_d3, 
  f_d3, f_d3, f_d3, f_d3, f_d3, f_d3, f_d3, f_d3
};

constexpr float f_d4 = 4.0F;

U3_ALIGN_DEFAULT
constexpr float f_all_d4[32] = {
  f_d4, f_d4, f_d4, f_d4, f_d4, f_d4, f_d4, f_d4, 
  f_d4, f_d4, f_d4, f_d4, f_d4, f_d4, f_d4, f_d4, 
  f_d4, f_d4, f_d4, f_d4, f_d4, f_d4, f_d4, f_d4, 
  f_d4, f_d4, f_d4, f_d4, f_d4, f_d4, f_d4, f_d4
};

constexpr float f_d5 = 5.0F;

U3_ALIGN_DEFAULT
constexpr float f_all_d5[32] = {
  f_d5, f_d5, f_d5, f_d5, f_d5, f_d5, f_d5, f_d5, 
  f_d5, f_d5, f_d5, f_d5, f_d5, f_d5, f_d5, f_d5, 
  f_d5, f_d5, f_d5, f_d5, f_d5, f_d5, f_d5, f_d5, 
  f_d5, f_d5, f_d5, f_d5, f_d5, f_d5, f_d5, f_d5
};

constexpr float f_d6 = 6.0F;

U3_ALIGN_DEFAULT
constexpr float f_all_d6[32] = {
  f_d6, f_d6, f_d6, f_d6, f_d6, f_d6, f_d6, f_d6, 
  f_d6, f_d6, f_d6, f_d6, f_d6, f_d6, f_d6, f_d6, 
  f_d6, f_d6, f_d6, f_d6, f_d6, f_d6, f_d6, f_d6, 
  f_d6, f_d6, f_d6, f_d6, f_d6, f_d6, f_d6, f_d6
};

constexpr float f_d128 = 128.0F;

U3_ALIGN_DEFAULT
constexpr float f_all_d128[32] = {
  f_d128, f_d128, f_d128, f_d128, f_d128, f_d128, f_d128, f_d128, 
  f_d128, f_d128, f_d128, f_d128, f_d128, f_d128, f_d128, f_d128, 
  f_d128, f_d128, f_d128, f_d128, f_d128, f_d128, f_d128, f_d128, 
  f_d128, f_d128, f_d128, f_d128, f_d128, f_d128, f_d128, f_d128
};

constexpr float f_d255 = 255.0F;

U3_ALIGN_DEFAULT
constexpr float f_all_d255[32] = {
  f_d255, f_d255, f_d255, f_d255, f_d255, f_d255, f_d255, f_d255, 
  f_d255, f_d255, f_d255, f_d255, f_d255, f_d255, f_d255, f_d255, 
  f_d255, f_d255, f_d255, f_d255, f_d255, f_d255, f_d255, f_d255, 
  f_d255, f_d255, f_d255, f_d255, f_d255, f_d255, f_d255, f_d255
};

constexpr float f_d1_to_d2 = f_d1 / f_d2;

U3_ALIGN_DEFAULT
constexpr float f_all_d1_to_2[32] = {
  f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, 
  f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, 
  f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, 
  f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2, f_d1_to_d2
};

constexpr float f_d1_to_d3 = f_d1 / f_d3;

U3_ALIGN_DEFAULT
constexpr float f_all_d1_to_3[32] = {
  f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, 
  f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, 
  f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, 
  f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3, f_d1_to_d3
};

constexpr float f_d1_to_d6 = f_d1 / f_d6;

U3_ALIGN_DEFAULT
constexpr float f_all_d1_to_6[32] = {
  f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, 
  f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, 
  f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, 
  f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6, f_d1_to_d6
};

constexpr float f_d1_to_d255 = f_d1 / f_d255;

U3_ALIGN_DEFAULT
constexpr float f_all_d1_to_255[32] = {
  f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, 
  f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, 
  f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, 
  f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255, f_d1_to_d255
};

constexpr float f_d2_to_d3 = f_d2 / f_d3;

U3_ALIGN_DEFAULT
constexpr float f_all_d2_to_3[32] = {
  f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, 
  f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, 
  f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, 
  f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3, f_d2_to_d3
};

U3_ALIGN_DEFAULT
constexpr float f_once_d1[32] = { 
  f_d1, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, 
  f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, 
  f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, 
  f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0, f_d0
};
// clang-format on
}   // namespace libs::optim::s16bit::consts
