#pragma once
/**
\file       enum-bufs-flags.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_bufs
*/

namespace libs::bufs
{
///  Перечисление различных флагов, общих для всего Bufs
enum class BufsFlags : std::uint32_t
{
  empty       = 0x00,   //< Флаг отсутствия данных
  request2hsl = 0x01,   //< Флаг требования произвести конвертацию в HSL (или обновить HSL) из буфера с оригинальными данными (RGB24/YUY2/I420/etc)
  unknown     = 0x0F,   //< Не определенно для общности
  max_bound   = 0x10    //< Максимальное значение типа для границы
};

inline std::uint32_t
enum_to_raw (const BufsFlags& val)
{
  return ::libs::utility::casts::static_cast_helper< std::uint32_t > (val);
}
}   // namespace libs::bufs
