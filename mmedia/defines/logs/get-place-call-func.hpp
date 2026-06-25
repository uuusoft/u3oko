#pragma once
/**
\file       get-place-call-func.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
*/

/// old shit
/// Функция для формирования текстового описания точки вызова (имя функции + номер строки)
/// \param[in]  file имя файла
/// \param[in]  line номер строки
/// \return     текстовое описание точки вызова
inline std::string
get_place_call (const char* file, std::int32_t line)
{
  std::string ret;

  ret.reserve (256);
  ret += file;
  ret += ":";
  ret += std::to_string (line);
  return ret;
}
