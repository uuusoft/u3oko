#pragma once
/**
\file       rgb24_to_rgb32.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_optim_gen_convert
*/

namespace libs::optim::convert::rgb24_rgb32
{
void alu (
  const std::uint8_t* rgb24_buf,
  std::uint32_t       stride_rgb24,
  std::uint32_t       width,
  std::uint32_t       height,
  std::uint8_t*       rgb32_buf,
  std::uint32_t       stride_rgb32,
  std::uint32_t       max_size_buf_rgb32,
  std::uint8_t        fill_alpha = 0);
}   // namespace libs::optim::convert::rgb24_rgb32
