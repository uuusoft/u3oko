/**
\file       bits_one_source_or_alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.07.2017

\project    u3_optim_libs_bits
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "../bits_one_source_move_alg.hpp"
#include "bits_one_source_or_ops.hpp"

namespace libs::optim::s16bit::bits::one_source::or_op
{
struct TFiller final {
  TFiller () :
    val_ (0)
  {
  }

  ~TFiller ()
  {
  }

  void
  init (TParams& params)
  {
    val_ = params.filling_;
  }

  void
  update (std::int16_t* buf)
  {
    *buf |= val_;
  }


  private:
  std::int16_t val_;   //<
};


void
alu (::libs::optim::io::MCallInfo& info)
{
  one_source::move_alg< TFiller, 1 > (info);
}
}   // namespace libs::optim::s16bit::bits::one_source::or_op
