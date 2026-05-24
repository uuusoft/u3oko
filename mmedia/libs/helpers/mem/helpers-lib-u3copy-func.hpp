#pragma once
/**
\file       helpers-lib-u3copy-func.hpp
\date       25.08.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_helpers_lib
\brief      Обявление функции копирования блока памяти для всей системы
*/

namespace libs::helpers::mem
{
/// Функция копирования блока памяти, на ряде платформ используется ряд дополнительх проверок
void u3copy (const void* src, void* dst, std::size_t size);
}   // namespace libs::helpers::mem
