#pragma once
/**
\file       decorate-dll-name-funcs.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_mem_funcs
*/

namespace libs::utility::dlls
{
/// Функция для корректировки имени файла загружаемого кода в зависимости от типа ОС
/// Требуется, т.к. имя задается в конфигурационных файлах (xml,etc) без учета ОС
/// \param[in]  dll  базовое имя библиотеки
/// \return     имя библиотеки, совместимое с ОС
auto decorate_dll_name (const std::string&) -> std::string;
auto undecorate_dll_name (const std::string&) -> std::string;
auto get_prefix () -> std::string;
auto get_dll_suffix () -> std::string;
auto make_func_name_lib (const std::string&, const std::string&) -> std::string;
}   // namespace libs::utility::dlls
