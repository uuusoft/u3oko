#pragma once
/**
\file       helpers-lib-u3copy-func.hpp
\date       25.08.2016
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
\brief      Обявление функции копирования блока памяти для всей системы
*/

namespace libs::helpers::mem
{
/// Функция копирования блока памяти, на ряде платформ используется ряд дополнительх проверок
auto u3copy (const void*, void*, std::size_t) -> void;
}   // namespace libs::helpers::mem
