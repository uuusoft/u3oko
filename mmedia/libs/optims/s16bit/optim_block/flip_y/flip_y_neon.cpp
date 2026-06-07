/**
\file       flip_y_neon.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_block
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "flip_y.hpp"
#include "flip_y_move_alg.hpp"

#ifdef U3_CPU_ARM

namespace libs::optim::s16bit::block::flip_y
{
struct TFlipperNeon final {
  TFlipperNeon ()
  {
  }

  void
  init (TParams& params)
  {
  }

  U3_SET_TARGET_CPU (+simd)
  void
  update (std::uint8_t* str1, std::uint8_t* str2)
  {
    int16x8_t temp1;
    int16x8_t temp2;

    temp1 = vld1q_s16 (::libs::helpers::casts::reinterpret_cast_helper< const std::int16_t* > (str1));
    temp2 = vld1q_s16 (::libs::helpers::casts::reinterpret_cast_helper< const std::int16_t* > (str2));

    vst1q_s16 (::libs::helpers::casts::reinterpret_cast_helper< std::int16_t* > (str1), temp2);
    vst1q_s16 (::libs::helpers::casts::reinterpret_cast_helper< std::int16_t* > (str2), temp1);
  }
};


U3_SET_TARGET_CPU (+simd)
void
neon (::libs::optim::io::MCallInfo& info)
{
  move_alg< TFlipperNeon, 16 > (info);
}
}   // namespace libs::optim::s16bit::block::flip_y

#endif
