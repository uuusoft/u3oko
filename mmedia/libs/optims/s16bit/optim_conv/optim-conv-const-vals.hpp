#pragma once
/**
\file       optim-conv-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_conv
*/

/// U3-REFACT Константа как define т.к используется еще и в ассемблерном коде
#ifndef U3_SHIFT_MUL_KOEFF_CONVOLUTION
#  define U3_SHIFT_MUL_KOEFF_CONVOLUTION 14
#endif

namespace libs::optim::s16bit::conv::consts
{
constexpr std::int32_t shift_for_base_mul_koeff = U3_SHIFT_MUL_KOEFF_CONVOLUTION;   //<
constexpr std::int32_t base_mul_koeff           = 4096 * 4;                         //<
}   // namespace libs::optim::s16bit::conv::consts


namespace libs::optim::s16bit::conv::consts::bufs
{
constexpr std::uint32_t max_size_core_conv            = 101;                                                                                                  //< Максимальное значение размера свертки
constexpr std::uint32_t half_max_size_core_conv       = max_size_core_conv / 2;                                                                               //< Половина максимального значения свертки
constexpr std::uint32_t x_off_edge_conv               = (half_max_size_core_conv * sizeof (std::int16_t) + 63) & ::libs::helpers::mem::consts::align_ptr64;   //< Смещение данных строки от краев буфера
constexpr std::uint32_t x_add_conv                    = x_off_edge_conv * 2;                                                                                  //<
constexpr std::uint32_t max_align_block_by_y_for_algs = 16;                                                                                                   //< Максимальный размер выравнивания по вертикали для всех алогоритмов
}   // namespace libs::optim::s16bit::conv::consts::bufs
