#pragma once
/**
\file       helpers-lib-decorate-dll-name-funcs.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_mem_funcs
*/

namespace libs::helpers::dlls
{
/// Функция для корректировки имени файла загружаемого кода в зависимости от типа ОС
/// Требуется, т.к. имя задается в конфигурационных файлах (xml,etc) без учета ОС
/// \param[in]  dll  базовое имя библиотеки
/// \return     имя библиотеки, совместимое с ОС
std::string decorate_dll_name (const std::string& dll);
std::string undecorate_dll_name (const std::string& dll);
std::string get_prefix ();
std::string get_dll_suffix ();
}   // namespace libs::helpers::dlls
