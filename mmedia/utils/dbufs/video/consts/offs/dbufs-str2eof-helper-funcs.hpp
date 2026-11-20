#pragma once
/**
\file       dbufs-str2eof-helper-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
*/

namespace utils::dbufs::video::consts::offs
{
/// Вспомогательная свободная функция для конвертации строки в индекс буфера
/// \param[in]  str  строка
/// \return     тип буфера
auto str2eoffbuf (const std::string& str) -> const off_buf_type;
}   // namespace utils::dbufs::video::consts::offs
