#pragma once
/**
\file       helpers-lib-check-buf-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/

// old shit
namespace libs::helpers::mem
{
/// функия проверки блока памяти на чтение и запись
bool check_buf (void* buf, const std::uint32_t size);
/// функия проверки блока памяти на чтение и запись
bool check_read_buf (const void* sbuf, const std::uint32_t size);
}   // namespace libs::helpers::mem
