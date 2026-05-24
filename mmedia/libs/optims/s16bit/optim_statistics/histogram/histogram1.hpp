#pragma once
/**
\file       histogram1.hpp
\date       01.05.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_statistic

Функции выводит в заданный 256 std::uint32_t массив частоты поялвления соотвествующих
байтов в источнике. Формат источника 16 битовое слово, но перед вычислением
формат усекается до беззнакового байта.
Полезна при построении гистограммы изображения.
*/

namespace libs::optim::s16bit::statistics::histogram
{
void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::statistics::histogram
