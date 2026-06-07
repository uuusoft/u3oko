/**
\file       flip_y_alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_block
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "flip_y.hpp"
#include "flip_y_move_alg.hpp"

namespace libs::optim::s16bit::block::flip_y
{
struct TFlipperAlu final {
  TFlipperAlu ()
  {
  }

  void
  init (TParams& params)
  {
  }

  void
  update (std::uint8_t* str1, std::uint8_t* str2)
  {
    const int temp = *::libs::helpers::casts::reinterpret_cast_helper< int* > (str1);

    *::libs::helpers::casts::reinterpret_cast_helper< int* > (str1) = *::libs::helpers::casts::reinterpret_cast_helper< int* > (str2);
    *::libs::helpers::casts::reinterpret_cast_helper< int* > (str2) = temp;
  }
};


void
alu (::libs::optim::io::MCallInfo& info)
{
  move_alg< TFlipperAlu, 4 > (info);
}
}   // namespace libs::optim::s16bit::block::flip_y
