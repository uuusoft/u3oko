#pragma once
/**
\file       points-enum.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj
{
/// Тип точки соединения объекта
enum class Points : std::uint32_t
{
  input   = 0x00,   //< Входная точка объекта
  output  = 0x01,   //< Выходная точка объекта
  unknown = 0xFF    //<
};
}   // namespace libs::icore::impl::var1::obj
