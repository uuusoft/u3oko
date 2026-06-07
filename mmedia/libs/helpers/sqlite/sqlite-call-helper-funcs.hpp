#pragma once
/**
\file       sqlite-call-helper-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.09.2018
\project    mevents
*/

namespace libs::helpers::sqlite
{
/// sqlite3_exec
/// \param[in]  pbase  sqlite
/// \param[in]  cmd    sql
/// \param[in]  info
void call_exec (sqlite3* pbase, const std::string& cmd, const std::string& info = std::string ());

std::string to_sql_str (const std::string& val);
}   // namespace libs::helpers::sqlite
