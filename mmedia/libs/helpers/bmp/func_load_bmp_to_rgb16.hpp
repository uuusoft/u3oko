#pragma once
/**
\file       func_load_bmp_to_s16bit.hpp
\brief      Function for load data from bmp32 file and convert to r16g16b16 format
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_helpers_lib
*/

//  old shit
namespace libs::helpers::bmp
{
#if 0
bool load_bmp_to_s16bit (
  ::libs::optim::s16bit::convert::rgb32_rgb48_funct convert_funct,
  ::libs::optim::io::mtcall_func               mirror_funct,
  const std::string&                                name_file,
  std::int16_t**                                    r16,
  std::int16_t**                                    g16,
  std::int16_t**                                    b16,
  std::int32_t*                                     width,
  std::int32_t*                                     height,
  std::int32_t*                                     stride_byte,
  int                                               need_div_stride_byte,
  std::int32_t*                                     max_size_buf);
#endif
}   // namespace libs::helpers::bmp
