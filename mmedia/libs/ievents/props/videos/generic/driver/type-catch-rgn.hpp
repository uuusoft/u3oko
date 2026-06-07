#pragma once
/**
\file       type-catch-rgn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::driver
{
/// Перечисление различных регионов при захвате изображения с экрана
enum class CatchRgns : std::uint32_t
{
  usual       = 0x00,   //< Значение по умолчанию для общности
  desktop     = 0x01,   //< Десктоп
  hwnd        = 0x02,   //< Указанное окно
  selection   = 0x03,   //< Выделение из дескотопа
  cursor_area = 0x04,   //< Область связанная с курсором
  unknown     = 0xFF    //< Не определенно для общности
};

inline constexpr CatchRgns
catch_rgn_from_raw_value (std::uint32_t val)
{
  return ::libs::helpers::casts::static_cast_helper< CatchRgns > (val);
}
}   // namespace libs::ievents::props::videos::generic::driver
