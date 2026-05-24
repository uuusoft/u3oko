#pragma once
/**
\file       quant_tables.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/

namespace libs::optim::s16bit::freq::dct::b8x8::helpers::quant::consts
{
/// Таблица квантования - опорная, для яркости используется для генерации реальных таблиц квантования
/// на основе текущих устноавок кодека
/// Взята из jpeg
const std::int32_t lum_quant_table[b8x8::consts::count_elements_macroblock] = {
  16, 11, 10, 16, 24, 40, 51, 61, 12, 12, 14, 19, 26, 58, 60, 55, 14, 13, 16, 24, 40, 57, 69, 56, 14, 17, 22, 29, 51, 87, 80, 62, 18, 22, 37, 56, 68, 109, 103, 77, 24, 35, 55, 64, 81, 104, 113, 92, 49, 64, 78, 87, 103, 121, 120, 101, 72, 92, 95, 98, 112, 100, 103, 99
};

/// Таблица квантования - опорная, для цвета
/// Взята из jpeg
const std::int32_t chrom_quant_table[b8x8::consts::count_elements_macroblock] = {
  17, 18, 24, 47, 99, 99, 99, 99, 18, 21, 26, 66, 99, 99, 99, 99, 24, 26, 56, 99, 99, 99, 99, 99, 47, 66, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
};
}   // namespace libs::optim::s16bit::freq::dct::b8x8::helpers::quant::consts
