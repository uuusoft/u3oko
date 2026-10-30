/**
\file       sqlite-call-helper-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       06.06.2022
*/
#include "../utility-lib-includes_int.hpp"
#include "sqlite3.h"
#include "sql-resource-managment-helpers.hpp"
#include "sqlite-call-helper-funcs.hpp"

// old shit
namespace libs::utility::sqlite
{
void
call_exec (
  sqlite3*           pbase,
  const std::string& cmd,
  const std::string& info)
{
  ::libs::utility::checks::throw_ifn (!cmd.empty ());
  ::libs::utility::checks::throw_ifn (pbase);

  MemoryHandler sql_error;

  const auto res = sqlite3_exec (
    pbase,
    cmd.c_str (),
    nullptr,
    nullptr,
    sql_error.update_as< char* > ());

  ::libs::utility::checks::throw_ifn (SQLITE_OK == res, "sql " + info + ", " + cmd + std::string (":") + (sql_error.get_as< char* > () ? sql_error.get_as< char* > () : "?errsql?"));
}
}   // namespace libs::utility::sqlite
