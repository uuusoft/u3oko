/**
\file       sqlite-call-helper-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       06.06.2022
\project    u3_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"

#ifndef U3_DBG_EXTERNAL_LIB_SKIP_SQLITE

#  include "sqlite3.h"
#  include "../helpers-lib-includes_int.hpp"
#  include "sql-resource-managment-helpers.hpp"
#  include "sqlite-call-helper-funcs.hpp"

namespace libs::helpers::sqlite
{
void
call_exec (
  sqlite3*           pbase,
  const std::string& cmd,
  const std::string& info)
{
  U3_ASSERT (!cmd.empty ());
  U3_ASSERT (pbase);

  MemoryHandler sql_error;

  const auto res = sqlite3_exec (
    pbase,
    cmd.c_str (),
    nullptr,
    nullptr,
    sql_error.update_as< char* > ());

  U3_CHECK (
    SQLITE_OK == res,
    "sql " + info + ", " + cmd + std::string (":") + (sql_error.get_as< char* > () ? sql_error.get_as< char* > () : "?errsql?"));

  // const std::string err_msg = "" + info + ":" + (sql_error ? sql_error : "?errsql?");
  // sqlite3_free (sql_error);
  // U3_THROW_EXCEPTION (err_msg);
}


std::string
to_sql_str (const std::string& val)
{
  return "'" + val + "'";
}
}   // namespace libs::helpers::sqlite

#endif
