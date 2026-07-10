#pragma once
/**
\file       mem-copy-raw-func.hpp
\date       25.08.2016
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
\brief      Обявление функции копирования блока памяти для всей системы
*/

namespace libs::utility::mem
{
/// Функция копирования блока памяти, на ряде платформ используется ряд дополнительх проверок
auto mem_copy_raw (const void*, void*, std::size_t) -> void;
}   // namespace libs::utility::mem
