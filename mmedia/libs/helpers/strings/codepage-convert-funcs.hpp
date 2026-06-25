#pragma once
/**
\file       codepage-convert-funcs.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/

namespace libs::helpers::strings
{
/// Вспомогательная функция для конвертации строки в кодировке w(16/32) в строку с кодировкой utf8
/// \param[in]  str входная строка в кодировке w(16/32)
/// \retrun     выходная строка к кодировке utf8
std::string wstring2utf8 (const std::wstring&);
}   // namespace libs::helpers::strings
