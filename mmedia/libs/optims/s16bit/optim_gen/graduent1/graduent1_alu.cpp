/**
\file       graduent1_alu.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "graduent1.hpp"

namespace libs::optim::s16bit::gen::graduent1
{
void
alu (::libs::optim::io::MCallInfo& cinfo)
{
  check (cinfo);

  auto&         dst        = cinfo.dsts_[0];
  std::int16_t* buf        = dst.buf ();
  const auto    stride     = dst.stride_;
  const auto    width      = dst.width_;
  const auto    height     = dst.height_;
  const auto*   ivals      = cinfo.params_.consts_[0];
  const auto    size_ivals = cinfo.params_.ints_[0];

  for (std::uint32_t y = 0; y < height; ++y)
  {
    for (std::uint32_t x = 0; x < width; ++x)
    {
      U3_ASSERT_NT (buf[x] < size_ivals, VTOLOG (buf[x]) + VTOLOG (size_ivals));
      const auto ival = ::libs::helpers::utils::ret_check_bound< std::int16_t > (buf[x], 0, size_ivals - 1);
      buf[x]          = ivals[ival];
    }
    buf = ::libs::helpers::mem::move_ptr (buf, stride);
  }
}
}   // namespace libs::optim::s16bit::gen::graduent1
