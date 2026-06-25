#pragma once
/**
\file       update_register_lib_func.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/

namespace libs::helpers::files
{
/// Функция производит указанное действие (регистрация/дерегистрация) с указанной библиотекой
bool update_register_lib (const std::string& path, bool need_reg);
}   // namespace libs::helpers::files
