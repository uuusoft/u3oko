#pragma once
/**
\file       filter-runs-enum.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_icore_lib
\brief      Объявление типа состояния в котором может находится объект графа обработки данных
*/

namespace libs::icore::impl::var1::obj
{
enum class FilterRuns : std::uint32_t
{
  stop    = 0x00,   //< Объект остановлен
  run     = 0x01,   //< Объект запущен
  pause   = 0x02,   //< Объект приостановлен
  unknown = 0xFF    //<
};
}   // namespace libs::icore::impl::var1::obj
