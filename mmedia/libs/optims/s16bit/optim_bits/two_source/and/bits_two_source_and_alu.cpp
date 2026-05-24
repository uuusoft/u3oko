/**
\file       bits_two_source_and_alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_bits
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "../bits_two_source_move_alg.hpp"
#include "bits_two_source_and_ops.hpp"

namespace libs::optim::s16bit::bits::two_source::and_op
{
struct TFiller {
  TFiller ()
  {
  }

  ~TFiller ()
  {
  }

  void
  init (TParams& params)
  {
  }

  void
  update (const std::int16_t* sbuf, std::int16_t* buf)
  {
    *buf &= *sbuf;
  }
};


void
alu (::libs::optim::io::MCallInfo& info)
{
  two_source::move_alg< TFiller, 1 > (info);
}
}   // namespace libs::optim::s16bit::bits::two_source::and_op
