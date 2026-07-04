#pragma once
/**
\file       sqlite-call-helper-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.09.2018
\project    mevents
*/

// old shit
namespace libs::utility::sqlite
{
/// sqlite3_exec
/// \param[in]  pbase  sqlite
/// \param[in]  cmd    sql
/// \param[in]  info
void call_exec (sqlite3*, const std::string&, const std::string& = std::string ());

template< typename T >
inline auto
to_sql_str (const T& val) -> std::string
{
  return "'" + std::string { val } + "'";
}
}   // namespace libs::utility::sqlite
